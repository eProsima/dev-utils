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

"""
Test system_utils methods.
"""

import os

from py_utils.system.system_utils import is_linux, is_windows


def test_is_test():
    assert True


def test_is_linux():

    # Test case 0: Running the script in its own system
    # NOTE: this could use same method as the function internally, but it is what it is.
    if os.name == 'posix':
        assert is_linux()

    if os.name == 'nt':
        assert not is_linux()

#     # Test case 1: Running the script on a Linux system
#     os.name = 'posix'
#     assert is_linux()

#     # Test case 2: Running the script on a Windows system
#     os.name = 'nt'
#     assert not is_linux()

#     # Test case 3: Running the script on a different operating system
#     os.name = 'mac'
#     assert not is_linux()


def test_is_windows():

    # Test case 0: Running the script in its own system
    # NOTE: this could use same method as the function internally, but it is what it is.
    if os.name == 'posix':
        assert not is_windows()

    if os.name == 'nt':
        assert is_windows()

#     # Test case 1: Running the script on a Linux system
#     os.name = 'posix'
#     assert not is_windows()

#     # Test case 2: Running the script on a Windows system
#     os.name = 'nt'
#     assert is_windows()

#     # Test case 3: Running the script on a different operating system
#     os.name = 'mac'
#     assert not is_windows()
