{
  description = "Nix build and development environment for eProsima dev-utils";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs }:
    let
      lib = nixpkgs.lib;
      systems = [
        "x86_64-linux"
        "x86_64-darwin"
        "aarch64-darwin"
      ];
      forAllSystems = f: lib.genAttrs systems (system: f system);
      mkScope = system:
        let
          pkgs = import nixpkgs {
            inherit system;
          };
          llvm =
            if pkgs ? llvmPackages_21 then
              pkgs.llvmPackages_21
            else
              pkgs.llvmPackages_latest;
          stdenvForBuild =
            if pkgs.stdenv.isDarwin && llvm ? libcxxStdenv then
              llvm.libcxxStdenv
            else
              pkgs.stdenv;
          repoVersion = "1.5.2";

          cmake_utils = stdenvForBuild.mkDerivation {
            pname = "cmake_utils";
            version = repoVersion;
            src = ./.;
            sourceRoot = "source/cmake_utils";

            nativeBuildInputs = [
              pkgs.cmake
            ];
          };

          py_utils = pkgs.python3Packages.buildPythonPackage {
            pname = "py_utils";
            version = repoVersion;
            src = ./.;
            sourceRoot = "source/py_utils";
            format = "setuptools";
            doCheck = false;
            pythonImportsCheck = [
              "py_utils"
            ];
          };

          hasFastDds =
            pkgs ? fastcdr
            && pkgs ? fastdds
            && lib.meta.availableOn pkgs.stdenv.hostPlatform pkgs.fastcdr
            && lib.meta.availableOn pkgs.stdenv.hostPlatform pkgs.fastdds;

          cpp_utils =
            if hasFastDds then
              stdenvForBuild.mkDerivation {
                pname = "cpp_utils";
                version = repoVersion;
                src = ./.;
                sourceRoot = "source/cpp_utils";

                nativeBuildInputs = [
                  pkgs.cmake
                  pkgs.ninja
                  pkgs.pkg-config
                ];

                buildInputs = [
                  cmake_utils
                  pkgs.fastcdr
                  pkgs.fastdds
                ];

                cmakeFlags = [
                  "-DBUILD_TESTS=OFF"
                ];

                doCheck = false;
              }
            else
              null;

          toolchain_probe = stdenvForBuild.mkDerivation {
            pname = "dev-utils-toolchain-probe";
            version = repoVersion;
            dontUnpack = true;

            buildPhase = ''
              cat > toolchain-probe.cpp <<'EOF'
              #include <iostream>

              int main()
              {
                  std::cout << "dev-utils toolchain probe" << std::endl;
                  return 0;
              }
              EOF

              $CXX -std=c++17 toolchain-probe.cpp -o toolchain-probe
            '';

            installPhase = ''
              mkdir -p "$out/bin"
              cp toolchain-probe "$out/bin/"
            '';
          };

          defaultComponents =
            [
              cmake_utils
              py_utils
              toolchain_probe
            ]
            ++ lib.optionals hasFastDds [
              cpp_utils
            ];

          defaultPackage = pkgs.buildEnv {
            name = "dev-utils";
            paths = defaultComponents;
          };

          devShell = (pkgs.mkShell.override {
            stdenv = stdenvForBuild;
          }) {
            inputsFrom =
              [
                cmake_utils
                py_utils
              ]
              ++ lib.optionals hasFastDds [
                cpp_utils
              ];

            packages =
              [
                pkgs.bashInteractive
                pkgs.cmake
                pkgs.git
                pkgs.ninja
                pkgs.pkg-config
                pkgs.python3
                toolchain_probe
                llvm.clang
              ]
              ++ lib.optionals (llvm ? libcxx) [
                llvm.libcxx
              ]
              ++ lib.optionals hasFastDds [
                pkgs.fastcdr
                pkgs.fastdds
              ];

            shellHook = ''
              export CC="${stdenvForBuild.cc}/bin/cc"
              export CXX="${stdenvForBuild.cc}/bin/c++"

              if [ -z "''${DEV_UTILS_CPP_UTILS_AVAILABLE:-}" ]; then
                export DEV_UTILS_CPP_UTILS_AVAILABLE="${if hasFastDds then "1" else "0"}"
              fi

              if [ "$DEV_UTILS_CPP_UTILS_AVAILABLE" = "0" ]; then
                echo "cpp_utils is not included in this Nix environment because nixpkgs does not expose both fastdds and fastcdr on ${system}."
              fi
            '';
          };
        in
        {
          inherit devShell;
          packages =
            {
              inherit
                cmake_utils
                py_utils
                toolchain_probe
                ;
              default = defaultPackage;
            }
            // lib.optionalAttrs hasFastDds {
              inherit cpp_utils;
            };
        };
    in
    {
      packages = forAllSystems (system: (mkScope system).packages);
      devShells = forAllSystems (system: {
        default = (mkScope system).devShell;
      });
    };
}
