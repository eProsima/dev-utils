# Copyright 2021 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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

###################################
# Formatter Tests
###################################

set(TEST_NAME formatter_tests)

set(TEST_SOURCES
        formatter_tests.cpp
        ${PROJECT_SOURCE_DIR}/src/cpp/exception/Exception.cpp
        ${PROJECT_SOURCE_DIR}/src/cpp/format/Formatter.cpp
    )

set(TEST_LIST
        object_use
        cast_string
        to_string
        serialization_operator_string
        use_in_exception
    )

set(TEST_EXTRA_LIBRARIES
    )

set(TEST_NEEDED_SOURCES
    )

add_unittest_executable(
        "${TEST_NAME}"
        "${TEST_SOURCES}"
        "${TEST_LIST}"
        "${TEST_EXTRA_LIBRARIES}"
        "${TEST_NEEDED_SOURCES}"
    )


###################################
# format utils Tests
###################################

set(TEST_NAME format_utils_tests)

set(TEST_SOURCES
        format_utils_tests.cpp
        ${PROJECT_SOURCE_DIR}/src/cpp/format/Formatter.cpp
        ${PROJECT_SOURCE_DIR}/src/cpp/format/format_utils.cpp
    )

set(TEST_LIST
        convert_to_lowercase
        container_to_stream
        generic_to_string
    )

set(TEST_EXTRA_LIBRARIES
    )

set(TEST_NEEDED_SOURCES
    )

add_unittest_executable(
        "${TEST_NAME}"
        "${TEST_SOURCES}"
        "${TEST_LIST}"
        "${TEST_EXTRA_LIBRARIES}"
        "${TEST_NEEDED_SOURCES}"
    )
