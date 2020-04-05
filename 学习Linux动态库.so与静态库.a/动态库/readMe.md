# 动态库.so
## GCC生成动态链接库
如果想创建一个动态链接库，可以使用 GCC 的-shared选项。输入文件可以是源文件、汇编文件或者目标文件。

另外还得结合-fPIC选项。-fPIC 选项作用于编译阶段，告诉编译器产生与位置无关代码（Position-Independent Code）。这样一来，产生的代码中就没有绝对地址了，全部使用相对地址，所以代码可以被加载器加载到内存的任意位置，都可以正确的执行。这正是共享库所要求的，共享库被加载时，在内存的位置不是固定的。
```
//从源文件生成动态链接库
gcc -fPIC -shared func.cpp -o libfunc.so

//或者从目标文件生成动态链接库
gcc -fPIC -c func.cpp -o func.o
gcc -shared func.o -o libfunc.so
```

//当然，必须要确保程序在运行时可以找到这个动态链接库。你可以将链接库放到标准目录下例如/usr/lib，或者设置一个合适的环境变量例如LIBRARY_PATH。不同系统，具有不同的加载链接库的方法
//把当前路径设置到环境变量中，程序才能加载到libfunc.so  也可以把链接库放到标准目录下例如/usr/lib,(或者设置软链接)
```
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
```
## GCC将动态链接库链接到可执行文件
如果希望将一个动态链接库链接到可执行文件，那么需要在命令行中列出动态链接库的名称，具体方式和普通的源文件、目标文件一样。请看下面的例子：
```
// 使用dl*等函数时，需要加上-ldl选项
gcc main.cpp -ldl libfunc.so -o main
```
将main.cpp和libfunc.so一起编译成可执行文件main。当main运行时，会动态地加载链接库libfunc.so。

```
//测试，计算一个int整数的平方
./main 10

```


## 查看库中的符号
nm xx.so
nm xx.a
```
//可以看到myfunc的符号
nm libfunc.so
```

# 静态库.a
在cmake中也编译了静态库libmathfunction.a




