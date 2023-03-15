# dev-utils Versions

This file includes the released versions of **dev-utils** project along with their contributions to the project.
The *Forthcoming* section includes those features added in `main` branch that are not yet in a stable release.

## Forthcoming

* New class **StdinEventHandler** to easily read from std::cin.
* New class **CommandReader** to easily read from std::cin commands synchronously.

## Version 0.2.0

* New sub-packages included:
  * **dev_utils** package with tools for programmers to help in implementation process
    * Code auto-generator for Custom Enumerations.

* Sub-packages updated:
  * **cmake_utils**
    * Support minimum version requirement when finding a package.
  * **cpp_utils**
    * Logging module
      * Simplify and fixed TSAN issue.
    * Math module
      * New Random Manager class
    * Types module
      * New Singleton Auxiliary class

* CI new features:
  * Address Sanitizer check for all tests.
  * Thread Sanitizer check for all tests.
  * `-Wall` warning level for CI.
  * Add Python linter check in CI.

## Version 0.1.0

* First version of **dev-utils**.
* Packages and functionality included:
  * **cmake_utils**: tools for CMake builds and common macros and functions.
  * **cpp_utils**: C++ library for utilities and implementations.
    * Event module
    * Exception module
    * Logging module
    * Macros module
    * Math module
    * Memory module
    * Pool module
    * Testing module
    * ThreadPool module
    * Time module
    * Types module
    * Wait module

* CI features:
  * CI based on Github actions.
  * Test for all the main modules.
