```
# 配置cmake，例如option参数
cmake -DUSE_MYMATH=ON .
cmake --build .

# 编译，链接
make

# 安装(把文件拷贝到相应的路径下)
[sudo] make install

# 测试用例
ctest
```
