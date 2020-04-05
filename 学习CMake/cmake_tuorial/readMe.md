```

mkdir build
cd build

# 配置cmake，例如option参数. 上级目录的CMakeLists.txt文件
cmake -DUSE_MYMATH=ON ..

# 编译，链接
make

# 安装(把文件拷贝到相应的路径下)
[sudo] make install

# 测试用例
ctest
```
