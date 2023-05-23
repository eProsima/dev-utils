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
This file contains utils to debug python code.
"""

import sys

from py_utils.logging.log_utils import logger, logging


def debug_module_introspection(obj, debug_level: int = logging.DEBUG):
    if not isinstance(obj, type(sys)):
        return

    module_name = obj.__name__
    importables = []
    for name in dir(obj):
        importables.append((name, type(getattr(obj, name))))

    logger.log(debug_level, f'{{MODULE: <{module_name}>; Importables: <{importables}>}}')


def debug_class_introspection(obj, debug_level: int = logging.DEBUG):
    """Log in debug introspection information regarding an object."""
    if not isinstance(obj, type):
        return

    # If module
    class_name = obj.__name__
    methods = [method_name for method_name in dir(obj) if callable(getattr(obj, method_name))]
    attributes = [method_name for method_name in dir(obj) if not callable(getattr(obj, method_name))]
    parent_classes = obj.__bases__
    logger.log(debug_level, f'{{CLASS: <{class_name}>; Methods: <{methods}>; Attributes: <{attributes}>}}; Bases: <{parent_classes}>')


def debug_object_introspection(obj, debug_level: int = logging.DEBUG):
    """Log in debug introspection information regarding an object."""
    # If module
    class_name = type(obj).__name__
    methods = [method_name for method_name in dir(obj) if callable(getattr(obj, method_name))]
    attributes = [method_name for method_name in dir(obj) if not callable(getattr(obj, method_name))]
    to_str = obj.__str__()
    logger.log(debug_level, f'{{OBJECT: <{to_str}>; Class: <{class_name}>; Methods: <{methods}>; Attributes: <{attributes}>}}')


def debug_variable_introspection(obj, debug_level: int = logging.DEBUG):
    """Log in debug introspection information regarding an object."""
    # If module
    if isinstance(obj, type(sys)):
        debug_module_introspection(obj, debug_level)
    elif isinstance(obj, type):
        debug_class_introspection(obj, debug_level)
    else:
        debug_object_introspection(obj, debug_level)


def debug_function_decorator(
        debug_level: int = logging.DEBUG):
    """Decorator to debug information regarding start, arguments and finish of a function."""
    def decorator(func):
        def wrapper(*args, **kwargs):
            logger.log(debug_level, f'Function <{func.__name__}> called with arguments: <{args}>, <{kwargs}>')
            result = func(*args, **kwargs)
            logger.log(debug_level, f'Function <{func.__name__}> finished with return: <{result}>')
            return result
        return wrapper

    if callable(debug_level):
        func = debug_level
        debug_level = logging.DEBUG
        return decorator(func)

    else:
        return decorator


def debug_separator(
        debug_level: int = logging.DEBUG):
    print()
    logger.log(debug_level, '####################################################################\n')
