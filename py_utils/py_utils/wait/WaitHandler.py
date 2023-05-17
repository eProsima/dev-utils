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

from enum import Enum
import threading


class AwakeReason(Enum):
    disabled = 0
    timeout = 1
    condition_met = 2


class WaitHandler:

    def __init__(self, enabled, init_value):
        self._value = init_value
        self._enabled = enabled
        self._lock = threading.Lock()
        self._condition = threading.Condition(self._lock)
        self._n_waiting_threads = 0

    # Get and set methods for the protected variable
    def get_value(self):
        with self._lock:
            return self._value

    def set_value(self, value):
        with self._lock:
            self._value = value
            self._condition.notify_all()

    # Enable/disable methods
    def enable(self):
        with self._lock:
            self._enable_nts()

    def disable(self):
        with self._lock:
            self._disable_nts()

    # Blocking disable method
    def blocking_disable(self):
        with self._lock:
            self._blocking_disable_nts()

    # Enabled method
    def enabled(self):
        with self._lock:
            return self._enabled_nts()

    def blank_predicate(_):
        return False

    # Wait method
    def wait(self, predicate=blank_predicate, timeout=None):
        with self._lock:

            self._n_waiting_threads += 1

            awaken_reason = self._condition.wait_for(
                lambda: not self._enabled_nts() or predicate(self._value),
                timeout)

            self._n_waiting_threads -= 1

            if not self._enabled:
                return AwakeReason.disabled
            elif not awaken_reason:
                return AwakeReason.timeout
            else:
                return AwakeReason.condition_met

    # Enable/disable methods
    def _enable_nts(self):
        self._enabled = True
        # It is not required to notify, as if it was disabled none thread would be waiting

    def _disable_nts(self):
        self._enabled = False
        self._condition.notify_all()

    # Blocking disable method
    def _blocking_disable_nts(self):
        self._enabled = False
        while self._n_waiting_threads > 0:
            self._condition.notify_all()

    # Blocking disable method
    def _enabled_nts(self):
        return self._enabled
