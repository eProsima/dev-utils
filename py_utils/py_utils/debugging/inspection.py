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
This file contains utils to get information regarding the stack of the execution.
It allows to get the module, class or function name where the execution currently is.
"""

import inspect


def get_calling_frame(depth: int = 1):
    # Get the calling frame
    calling_frame = inspect.currentframe()

    # Move up the stack frames based on depth
    for _ in range(depth):
        calling_frame = calling_frame.f_back

    return calling_frame


def get_function_name(depth: int = 1, extend: bool = False) -> str:

    if not extend:
        # Get the calling frame
        calling_frame = get_calling_frame(depth=depth + 1)

        # Retrieve the function name
        return inspect.getframeinfo(calling_frame).function

    else:
        return get_context(depth + 1)


def is_inside_class(depth: int = 1) -> bool:
    # Get the calling frame
    calling_frame = get_calling_frame(depth=depth + 1)

    # Check if the frame is there is a self or a cls variable
    return "self" in calling_frame.f_locals or "cls" in calling_frame.f_locals


def get_class_name(depth: int = 1, extend: bool = False) -> str:
    # Get the calling frame
    calling_frame = get_calling_frame(depth=depth + 1)

    result = None

    # Retrieve the class name if there is a self variable
    self_var = calling_frame.f_locals.get("self")
    cls_var = calling_frame.f_locals.get("cls")
    if self_var is not None:
        result = self_var.__class__.__name__

    # Retrieve the class name if there is a cls variable
    elif cls_var is not None:
        result = cls_var.__name__

    if result is None or not extend:
        return result

    else:
        return get_module_name(depth=depth + 1) + result


def get_module_name(depth: int = 1) -> str:
    # Get the calling frame
    calling_frame = get_calling_frame(depth=depth + 1)

    # Retrieve the module name
    module_name = inspect.getmodule(calling_frame).__name__
    return module_name


def get_context(depth: int = 1) -> str:
    # Retrieve the module name
    ctx_name = get_module_name(depth + 1)

    # If it is in a class, return its class name
    class_name = get_class_name(depth + 1)
    if class_name is not None:
        ctx_name += '.' + class_name

    ctx_name += '.' + get_function_name(depth + 1)

    return ctx_name


def get_variable_module(v) -> str:
    return inspect.getmodule(v).__name__
