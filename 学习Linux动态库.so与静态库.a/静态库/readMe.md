# 静态库.a
在cmake中也编译了静态库libmathfunction.a
## GCC生成静态链接库
静态库后缀通常以.a结尾，链接生成静态库时需要使用ar命令，格式：ar rcs xxx.a xxx.o，常用参数：

r：在库中插入（修改）模块（替换静态库）。当插入的模块名已经在库中存在，则替换同名的模块，如若干模块中有一个模块在库中不存在，则ar显示一个错误信息，并且不会替换其他同名模块

c：创建一个新的库。不管库是否存在，都将创建

s：创建目标文件索引，此参数在创建较大库时能加快时间。如果不需要创建索引，可改写成S参数；
如果.a文件缺少索引，可以使用ranlib命令来添加索引

```
//编译目标文件
gcc -c func.cpp -o func.o
//把目标文档归档。这里的ar相当于tar的作用，将多个目标打包
//程序ar配合参数rcs创建一个新库libfunc.a，并将命令行中列出的文件打包入其中
ar rcs libfunc.a func.o

//查看静态库中的文件
ar -t libfunc.a
```
## GCC将静态链接库链接到可执行文件
将main.cpp和libfunc.a一起编译链接成可执行文件main。
```
//-L路径，制定到哪里去找库文件
gcc main.cpp libfunc.a -L. -o main

//或者
//-l 库的名字(libfunc.a)
gcc main.cpp -L. -l func -o main
```

测试
```
//测试，计算一个int整数的平方
./main 10

```


## 查看库中的符号
nm xx.so
nm xx.a
```
//可以看到myfunc的符号
nm libfunc.a
```





