#ifndef FUNC_H
#define FUNC_H

//以C的形式，如果以C++形式会报错找不到myfunc。因为C、C++的符号有区别
extern "C"
{
  int myfunc(int x);
}

#endif //FUNC_H
