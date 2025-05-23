# Copyright 2023 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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

set(TEST_NAME CommandReaderTest)

set(TEST_SOURCES
        CommandReaderTest.cpp
    )
all_library_sources("${TEST_SOURCES}")

set(TEST_LIST
        trivial_create
    )

if (NOT WIN32)
    list(APPEND TEST_LIST
        read_lines_enum_1
        read_lines_enum_1_negative
        read_lines_enum_2_singleton
    )
endif()

set(TEST_EXTRA_LIBRARIES
        fastcdr
        fastdds
        cpp_utils
    )

add_unittest_executable(
    "${TEST_NAME}"
    "${TEST_SOURCES}"
    "${TEST_LIST}"
    "${TEST_EXTRA_LIBRARIES}"
    "${TEST_NEEDED_SOURCES}"
)
