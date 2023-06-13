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
This file contains decorators for debug.
"""

from functools import wraps

from py_utils.logging.log_utils import logger, logging
from py_utils.decorators.CustomFunctionDecorator import CustomFunctionDecorator
from py_utils.debugging.inspection import get_variable_module


def debug_function_decorator(
        debug_level: int = logging.DEBUG):
    """Decorator to debug information regarding start, arguments and finish of a function."""
    @wraps(debug_level)
    def decorator(func):

        @wraps(func)
        def wrapper(*args, **kwargs):
            logger.log(
                debug_level,
                f'Function <{func.__name__}> called with arguments: <{args}>, <{kwargs}>')
            result = func(*args, **kwargs)
            logger.log(
                debug_level,
                f'Function <{func.__name__}> finished with return: <{result}>')
            return result
        return wrapper

    if callable(debug_level):
        func = debug_level
        debug_level = logging.DEBUG
        return decorator(func)

    else:
        return decorator


class DebugFunctionDecorator(CustomFunctionDecorator):

    def __init__(self, *args, **kwargs):

        # Default values (may be changed by kwargs)
        self.debug_level = logging.DEBUG
        self.add_module = True

        super().__init__(*args, **kwargs)

    def wrapper(self, func, *args, **kwargs):

        if self.add_module:
            fun_str = get_variable_module(func) + '.' + func.__name__
        else:
            fun_str = func.__name__

        logger.log(
            self.debug_level,
            f'Function <{fun_str}> called with arguments: <{args}>, <{kwargs}>')
        result = func(*args, **kwargs)
        logger.log(
            self.debug_level,
            f'Function <{fun_str}> finished with return: <{result}>')
        return result
