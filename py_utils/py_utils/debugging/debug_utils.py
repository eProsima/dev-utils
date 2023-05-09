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

def object_introspection(obj):
    class_name = type(obj).__name__
    methods = [method_name for method_name in dir(obj) if callable(getattr(obj, method_name))]
    return f'{{Class: <{class_name}; Methods: {methods}}}'


def debug_function(func):
    def wrapper(*args, **kwargs):
        print(f'Function <{func.__name__}> called with arguments: <{args}>, <{kwargs}>')
        result = func(*args, **kwargs)
        print(f'Function <{func.__name__}> finished')
        return result
    return wrapper
