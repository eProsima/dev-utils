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

# Set list of tests that can fail
set_test_label_file(${CMAKE_CURRENT_SOURCE_DIR}/XFAIL.list "xfail")
# Set list of tests that can fail using TSAN
set_test_label_file(${CMAKE_CURRENT_SOURCE_DIR}/XTSAN.list "xtsan")

# Set list of tests that can fail in windows
if (WIN32)
    set_test_label_file(${CMAKE_CURRENT_SOURCE_DIR}/WINDOWS_XFAIL.list "xfail")
endif()
