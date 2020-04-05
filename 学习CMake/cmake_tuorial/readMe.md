## 外部构建
```
// 外部构建(在build文件夹里面构建)
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

## 打包
```
// 构建二进制版本，会生成Tutorial-1.0.1-Linux.sh和Tutorial-1.0.1-Linux.tar.gz
// 可能会报错，提示一些文件的权限不够，chmod
cpack --config CPackConfig.cmake
// 构建源代码版本，会生成Tutorial-1.0.1-Source.tar.Z
cpack --config CPackSourceConfig.cmake
```
