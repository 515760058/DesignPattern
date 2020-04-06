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


另外一篇博客
# Linux操作系统下动态库的编写与调用
- https://blog.csdn.net/pathuang68/article/details/4273904
包括以下内容：
1. 用c语言写动态库

1.1 用c语言静态方式调用动态库

1.2 用c语言动态方式调用动态库

1.3 用c++静态方式调用动态库

1.4 用c++动态方式调用动态库

2. 用c++语言写动态库

2.1 用c语言静态方式调用动态库

2.2 用c语言动态方式调用动态库

2.3 用c++语言静态方式调用动态库

2.4 用c++语言静态方式调用动态库



## 1. 用 c 语言写动态库：
```
/*
  * libsthc.h
  * Declarations for function add
  */
#include "stdio.h"
#include "stdlib.h"
#include "stdarg.h"

#ifdef __cplusplus
extern "C"
{
#endif

int add(int x, int y);

#ifdef __cplusplus
}
#endif
```
 
```
/*
  * libsthc.c
  * Implementation of function add declared in libsthc.h
  * in c language
  */
#include "libsthc.h"

int add(int x, int y)
{
     return x + y;
}
```
 

makefile
```
libsthc.so:libsthc.o
         gcc -shared libsthc.o -lc -o libsthc.so
libsthc.o:libsthc.c libsthc.h
         gcc -fPIC -c libsthc.c -o libsthc.o
all:libsthc.so
clean:
         rm -f *.o *.so
```
make 完成后，会生成一个动态库，即 libsthc.so 。为了使其他程序也可以使用该动态库，需要将库文件 libsthc.so 拷贝到 /usr/lib 目录下 ( 由于权限的问题，一般要以 root 的身分进行拷贝 ) ，为了使其他程序也可以使用该动态库，需要将头文件 libsthc.h 拷贝到 /usr/include 目录下 ( 由于权限的问题 , 一般要以 root 的身分进行拷贝 ) 。


### 1.1 用c语言静态方式调用动态库 libsthc.so ：
```
/*
  * ctest.c
  * Testing program for libsthc.so library
  * in c languange
  * by 玄机逸士
*/
#include "libsthc.h"

int main(void)
{
     printf("%d/n", add(1, 2));
     return 0;
}
```

makefile:
```
ctest:ctest.o
         gcc ctest.o -lsthc -o ctest
ctest.o:ctest.c
         gcc -c ctest.c -o ctest.o
all:ctest
clean:
         rm -f *.o ctest
```
### 1.2 用c语言动态方式调用动态库libsthc.so ：
```
/*cdltest.c*/
#include "stdio.h"
#include "stdlib.h"
#include "dlfcn.h"

int main(void){
         void *handle;
         int (*fcn)(int x, int y);
         const char *errmsg;
 
        /* open the library */
         handle = dlopen("libsthc.so", RTLD_NOW);
         if(handle == NULL)
         {
                   fprintf(stderr, "Failed to load libsthc.so: %s/n", dlerror());
                   return 1;
         }
         dlerror();

         //*(void **)(&fcn) = dlsym(handle, "add");            //ok
         fcn = dlsym(handle, "add");                           //ok
         if((errmsg = dlerror()) != NULL)
         {
                  printf("%s/n", errmsg);
                  return 1;
         }
         printf("%d/n", fcn(1, 5));

         dlclose(handle);
         return 0;
}
```

makefile
```
cdltest:cdltest.o
         gcc cdltest.o -ldl -lsthc -o cdltest
cdltest.o:cdltest.c
         gcc -c cdltest.c -o cdltest.o
all:cdltest
clean:
         rm -f *.o cdltest
```
 

### 1.3 用c++静态方式调用动态库libsthc.so ：
```
/*cpptest.cc*/
#include "libsthc.h"

using namespace std;
int main(void)
{

         printf("%d/n", add(1, 2));
         return 0;
}
```

makefile:
```
cpptest:cpptest.o
         g++ cpptest.o –o cpptest -lsthc
cpptest.o:cpptest.cc
         g++ -c cpptest.cc -Wno-deprecated -o cpptest.o
all:cpptest
clean:
         rm -f *.o cpptest
```
### 1.4 用c++动态方式调用动态库libsthc.so ：
```
/*cppdltest.cpp*/
#include "stdio.h"
#include "stdlib.h"
#include "dlfcn.h"

int main(void){
         void *handle;
         int (*fcn)(int x, int y);
         const char *errmsg;

         /* open the library */
         handle = dlopen("libsthc.so", RTLD_NOW);
         if(handle == NULL){
                   fprintf(stderr, "Failed to load libsthc.so: %s/n", dlerror());
                   return 1;
         }
         dlerror();

         *(void **)(&fcn) = dlsym(handle, "add");     //ok
         //fcn = dlsym(handle, "add");                        //not ok in c++
         if((errmsg = dlerror()) != NULL)
         {
                   printf("%s/n", errmsg);
                   return 1;
         }
         printf("%d/n", fcn(1, 5));
      
         dlclose(handle);
         return 0;
}
```
makefile
```
cppdltest:cppdltest.o
         g++ cppdltest.o -ldl -lsthc -o cppdltest
cppdltest.o:cppdltest.cpp
         g++ -c cppdltest.cpp -o cppdltest.o
all:cppdltest
clean:
         rm -f *.o cppdltest
```

## 2. 用c++语言写动态库：
```
/*
  * libsthcpp.h
  * Declarations for function cppadd
  */
#include "stdio.h"
#include "stdlib.h"
#include "stdarg.h"

#ifdef __cplusplus
extern "C" {
#endif

int cppadd(int x, int y);

#ifdef __cplusplus
}
#endif
```

```
/*
  * libsthcpp.cpp
  * Implementation of function cppadd declared in libsthcpp.h
  * in c++ language
  */
#include "libsthcpp.h"

int cppadd(int x, int y){
         return x + y;
}
```

makefile
```
libsthcpp.so:libsthcpp.o
         g++ -g -shared -Wl libsthcpp.o -lc -o libsthcpp.so
libsthcpp.o:libsthcpp.cc libsthcpp.h
         g++ -g -fPIC -c libsthcpp.cc -o libsthcpp.o
all:libsthcpp.so
clean:
         rm -f *.o *.so
```
make 完成后，会生成一个动态库，即 libsthcpp.so 。为了使其他程序也可以使用该动态库，需要将库文件 libsthcpp.so 拷贝到 /usr/lib 目录下 ( 由于权限的问题，一般要以 root 的身分进行拷贝 ) ，为了使其他程序也可以使用该动态库，需要将头文件 libsthcpp.h 拷贝到 /usr/include 目录下 ( 由于权限的问题 , 一般要以 root 的身分进行拷贝 ) 。
### 2.1 用c语言静态方式调用动态库libsthcpp.so
```
/*
  * ctest.c
  * Testing program for libsthcpp.so library
  * in c languange
  * by 玄机逸士
*/
#include "libsthcpp.h"
int main(void){
         printf("%d/n", cppadd(1, 2));
         return 0;
}
```
makefile
```
ctest:ctest.o
         gcc ctest.o -lsthcpp -o ctest
ctest.o:ctest.c
         gcc -c ctest.c -o ctest.o
all:ctest
clean:
         rm -f *.o ctest
```
### 2.2 用c语言动态方式调用动态库libsthcpp.so
```
/*cdltest.c*/
#include "stdio.h"
#include "stdlib.h"
#include "dlfcn.h"

int main(void){
         void *handle;
         int (*fcn)(int x, int y);
         const char *errmsg;

         /* open the library */
         handle = dlopen("libsthcpp.so", RTLD_NOW);
         if(handle == NULL) {
                   fprintf(stderr, "Failed to load libsthc.so: %s/n", dlerror());
                   return 1;
         }
         dlerror();
 
         //*(void **)(&fcn) = dlsym(handle, "cppadd");       //ok in c and c++
         fcn = dlsym(handle, "cppadd");                      //ok in c, but not in c++
         if((errmsg = dlerror()) != NULL)
         {
                   printf("%s/n", errmsg);
                   return 1;
         }

         printf("%d/n", fcn(1, 5));
         dlclose(handle);
         return 0;

}
```

makefile
```
cdltest:cdltest.o
         gcc cdltest.o -ldl -lsthcpp -o cdltest
cdltest.o:cdltest.c
         gcc -c cdltest.c -o cdltest.o
all:cdltest
clean:
         rm -f *.o cdltest
```
### 2.3 用c++语言静态方式调用动态库libsthcpp.so
```
/*
  * cpptest.cpp
  * Testing program for libsthc.so library written in c language
  * in c++ languange
  * by 玄机逸士
*/
#include "libsthcpp.h"
#include "iostream.h"

int main(void){
         cout << cppadd(1, 2) << endl;
         return 0;
}
```

makefile
```
cpptest:cpptest.o
         g++ cpptest.o -lsthcpp -o cpptest
cpptest.o:cpptest.cpp
         g++ -c cpptest.cpp -Wno-deprecated -o cpptest.o
all:cpptest
clean:
         rm -f *.o cpptest
```
### 2.4 用c++语言动态方式调用动态库libsthcpp.so
```
/*cppdltest.cpp*/
#include "stdio.h"
#include "stdlib.h"
#include "dlfcn.h"

int main(void){
         void *handle;
         int (*fcn)(int x, int y);
         const char *errmsg;

         /* open the library */
         handle = dlopen("libsthcpp.so", RTLD_NOW);
         if(handle == NULL) {
                   fprintf(stderr, "Failed to load libsthc.so: %s/n", dlerror());
                   return 1;
         }
         dlerror();

         *(void **)(&fcn) = dlsym(handle, "cppadd");         //ok in c and c++

         //fcn = dlsym(handle, "cppadd");                             //ok in c, but not in c++
         if((errmsg = dlerror()) != NULL)
         {
                   printf("%s/n", errmsg);
                   return 1;
         }

         printf("%d/n", fcn(1, 5));

         dlclose(handle);
         return 0;
}
```
makefile
```
cppdltest:cppdltest.o
         g++ cppdltest.o -ldl -lsthcpp -o cppdltest
cppdltest.o:cppdltest.cpp
         g++ -c cppdltest.cpp -o cppdltest.o
all:cppdltest
clean:
         rm -f *.o cppdltest
```

