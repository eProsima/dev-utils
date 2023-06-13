
from py_utils.logging.log_utils import logger, logging, activate_debug
from py_utils.decorators.debugging import DebugFunctionDecorator, debug_function_decorator



@DebugFunctionDecorator(3)
def foo(x):
    print(f'INSIDE FOO {x}')


foo(1)
print(foo.__name__)


activate_debug()



@DebugFunctionDecorator
def foo2(x):
    print(f'INSIDE FOO2 {x}')


foo2(3)
print(foo.__name__)




@DebugFunctionDecorator(debug_level=logging.WARNING, add_module=False)
def foo3(x):
    print(f'INSIDE FOO3 {x}')


foo3(7)
print(foo3.__name__)


@DebugFunctionDecorator(4, k=2)
def foo4(x, y, z=1, a=3):
    print(f'INSIDE FOO4 {x} , {y}, {a}')


foo4(7, 'some', a='other')
print(foo4.__name__)



@debug_function_decorator
def foo6(x):
    print(f'INSIDE FOO6 {x}')


foo6(7)
print(foo6.__name__)


@debug_function_decorator(20)
def foo7(x, y, z=1, a=3):
    print(f'INSIDE FOO7 {x} , {y}, {a}')


foo7(7, 'some', a='other')
print(foo7.__name__)
