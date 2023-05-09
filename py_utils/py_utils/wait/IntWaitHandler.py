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

from py_utils.wait.WaitHandler import WaitHandler


class IntWaitHandler(WaitHandler):

    def __init__(self, enabled, init_value: int = 0):
        super().__init__(enabled, init_value)

    def increase(self, value: int = 1):
        with self._lock:
            self._value += value
            self._condition.notify_all()

    def decrease(self, value: int = 1):
        with self._lock:
            self._value -= value
            self._condition.notify_all()

    def wait_equal(self, value, timeout=None):
        return super().wait(predicate=(lambda v: value == v), timeout=timeout)

    def wait_greater_equal(self, value, timeout=None):
        return super().wait(predicate=(lambda v: v >= value), timeout=timeout)

    def wait_greater(self, value, timeout=None):
        return super().wait(predicate=(lambda v: v > value), timeout=timeout)
