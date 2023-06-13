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

from functools import wraps


class CustomFunctionDecorator():

    def __init__(self, *args, **kwargs):
        self.func_ = None
        self.ctor_args_ = args
        self.ctor_kwargs_ = kwargs

        # If the decorator has no arguments, use the func argument passed
        if (len(args) == 1 and callable(args[0]) and len(kwargs) == 0):
            self.func_ = args[0]
            self.ctor_args_ = ()  # No arguments passed, so remove

        # If the decorator has arguments, check if any kwargs sets any of the internal attributes
        else:
            for attr in dir(self):
                if attr in kwargs.keys():
                    setattr(self, attr, kwargs[attr])

    def __call__(self, *args, **kwargs):
        # If decorator created without arguments, function already available
        # Also it means this is calling the actual function already
        if self.func_ is not None:
            return self.wrapper(self.func_, *args, **kwargs)

        # If created with args, this is only calling to set the function
        else:
            self.func_ = args[0]
            return self.__call__

    def wrapper(self, func, *args, **kwargs):
        # Call the function with the provided arguments
        return func(*args, **kwargs)

    def ctor_had_arguments(self):
        # Call the function with the provided arguments
        return len(self.ctor_args_) > 0 or len(self.ctor_kwargs_) > 0
