# Copyright 2022 Proyectos y Sistemas de Mantenimiento SL (eProsima).
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Return a list of all cpp and hpp files in library
# Arguments:
# TEST_SOURCES -> List of source files where new sources will be added
function(all_library_sources TEST_SOURCES)

    file(GLOB_RECURSE LIBRARY_SOURCES
            "${PROJECT_SOURCE_DIR}/src/cpp/**/*.c"
            "${PROJECT_SOURCE_DIR}/src/cpp/**/*.cpp"
            "${PROJECT_SOURCE_DIR}/src/cpp/**/*.cxx"
            "${PROJECT_SOURCE_DIR}/src/cpp/**/*.h"
            "${PROJECT_SOURCE_DIR}/src/cpp/**/*.hpp"
            "${PROJECT_SOURCE_DIR}/src/cpp/**/*.hxx"
            "${PROJECT_SOURCE_DIR}/test/TestUtils/**/*.cpp"
            "${PROJECT_SOURCE_DIR}/test/TestUtils/*.cpp"
        )
    set(NEW_TEST_SOURCES "${TEST_SOURCES};${LIBRARY_SOURCES}")
    set(TEST_SOURCES ${NEW_TEST_SOURCES} PARENT_SCOPE)

endfunction()

# Return a list of all hpp files in library
# Arguments:
# TEST_SOURCES -> List of source files where new sources will be added
function(all_header_sources TEST_SOURCES)

    file(GLOB_RECURSE LIBRARY_SOURCES
            "${PROJECT_SOURCE_DIR}/src/cpp/**/*.h"
            "${PROJECT_SOURCE_DIR}/src/cpp/**/*.hpp"
            "${PROJECT_SOURCE_DIR}/src/cpp/**/*.hxx"
        )
    set(NEW_TEST_SOURCES "${TEST_SOURCES};${LIBRARY_SOURCES}")
    set(TEST_SOURCES ${NEW_TEST_SOURCES} PARENT_SCOPE)

endfunction()

# Generate an API test with an "include_all" file
# Arguments:
function(add_api_test)

    # Configure template file with test
    configure_file(
        ${cmake_utils_CPP_TEMPLATES_PATH}/test/api_test.cpp.in
        ${PROJECT_BINARY_DIR}/test/api/api_test.cpp)

    add_unittest_executable(
            "api_test"                                      # TEST_NAME
            "${PROJECT_BINARY_DIR}/test/api/api_test.cpp"   # TEST_SOURCES
            ""                                              # TEST_LIST
            "${PROJECT_NAME}"                               # TEST_EXTRA_LIBRARIES
        )

endfunction()
