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
Test inspection function.
"""

from py_utils.debugging.inspection import (
    inspect_is_inside_class,
    inspect_get_class_name,
    inspect_get_module_name,
    inspect_get_function_name,
)

"""
inspect_is_inside_class
"""


def test_inspect_is_inside_class__inside():
    class MyClass:
        def foo(self):
            assert inspect_is_inside_class()
    MyClass().foo()


def test_inspect_is_inside_class__static():
    class MyClass:
        @staticmethod
        def foo():
            assert not inspect_is_inside_class()
    MyClass.foo()


def test_inspect_is_inside_class__static_classmethod():
    class MyClass:
        @classmethod
        def foo(cls):
            assert inspect_is_inside_class()
    MyClass.foo()


def test_inspect_is_inside_class__outside():
    assert not inspect_is_inside_class()


"""
inspect_get_class_name
"""


def test_inspect_get_class_name__inside():
    class MyClass:
        def foo(self):
            assert inspect_get_class_name() == "MyClass"
    MyClass().foo()


def test_inspect_get_class_name__static():
    class MyClass:
        @staticmethod
        def foo():
            assert inspect_get_class_name() is None
    MyClass.foo()


def test_inspect_get_class_name__static_classmethod():
    class MyClass:
        @classmethod
        def foo(cls):
            assert inspect_get_class_name() == "MyClass"
    MyClass.foo()


def test_inspect_get_class_name__outside():
    assert inspect_get_class_name() is None


"""
test_inspect_get_module_name
"""


def test_inspect_get_module_name():
    assert inspect_get_module_name() == "test_inspection"


"""
inspect_get_function_name
"""


def test_inspect_get_function_name():
    def outer_function():
        assert inspect_get_function_name() == "outer_function"
        assert inspect_get_function_name(depth=2) == "test_inspect_get_function_name"

        def inner_function():
            assert inspect_get_function_name() == "inner_function"
            assert inspect_get_function_name(depth=2) == "outer_function"
            assert inspect_get_function_name(depth=3) == "test_inspect_get_function_name"

        inner_function()

    outer_function()


def test_inspect_get_function_name__extend_with_class():
    class MyClass:
        def foo(self):
            assert (
                inspect_get_function_name(extend=True)
                == "test_inspection.MyClass.foo")
    MyClass().foo()


def test_inspect_get_function_name__extend_without_class():
    assert (
        inspect_get_function_name(extend=True)
        == "test_inspection.test_inspect_get_function_name__extend_without_class")
