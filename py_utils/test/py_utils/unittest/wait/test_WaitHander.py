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

import time
import threading

from py_utils.wait.WaitHandler import AwakeReason, WaitHandler
from py_utils.time.Timer import Timer


TEST_SLEEP_TIME = 0.5
TEST_RESIDUAL_TIME = 0.1


def test_ctor_trivial():
    waiter = WaitHandler(True, 0)  # noqa: F841


def test_wait_condition_met():
    # Create waiter disabled
    waiter = WaitHandler(True, 0)

    # Create thread that sleep for a while and then disable the handler
    def condition_met_waiter_function(waiter):
        time.sleep(TEST_SLEEP_TIME)
        waiter.set_value(1)
    t = threading.Thread(target=condition_met_waiter_function, args=(waiter,))
    t.start()

    # Create a Timer to check is actually waiting
    timer = Timer()

    # Wait till condition met
    awaken_reason = waiter.wait(lambda v: v == 1)
    assert awaken_reason == AwakeReason.condition_met

    elapsed = timer.elapsed()
    assert elapsed >= TEST_SLEEP_TIME and elapsed <= TEST_SLEEP_TIME + TEST_RESIDUAL_TIME


def test_wait_timeout():
    # Create waiter
    waiter = WaitHandler(True, 0)

    # Wait with timeout
    awaken_reason = waiter.wait(timeout=TEST_SLEEP_TIME)

    # Check that reason of awaken is timeout
    assert awaken_reason == AwakeReason.timeout


def test_wait_disable():
    # Create waiter disabled
    waiter = WaitHandler(False, 0)

    # Try wait
    awaken_reason = waiter.wait()
    assert awaken_reason == AwakeReason.disabled

    # Enable handler
    waiter.enable()

    # Create thread that sleep for a while and then disable the handler
    def disable_waiter_function(waiter):
        time.sleep(TEST_SLEEP_TIME)
        waiter.disable()
    t = threading.Thread(target=disable_waiter_function, args=(waiter,))
    t.start()

    # Wait till disabled
    awaken_reason = waiter.wait()
    assert awaken_reason == AwakeReason.disabled
