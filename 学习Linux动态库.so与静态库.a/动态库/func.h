#ifndef FUNC_H
#define FUNC_H

/*
extern "C" 是告诉编译器用C语言的方式给函数命名，如果以C++形式会报错找不到myfunc，因为C、C++的符号有区别：
由于C++存在函数重载，为了实现同样的函数名可因参数不同而存在，所以在处理这些函数时，会把函数名编译成不同的符号以便自己识别。
但当我们使用 extern "C" 时，编译器会标识为： _函数名
int test(int, int) -> _test
float test(float, float) -> _test
因此被 extern "C" 修饰过的函数也不再具备重载能力。
*/
extern "C"
{
  int myfunc(int x);
}

#endif //FUNC_H
