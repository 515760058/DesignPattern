# 使用MathFunctions.cpp源文件，构建MathFunctions库，生成libMathFunctions.a静态库文件
# 该静态库自己定义了mysqrt函数，用以替代系统中math.h的sqrt函数
add_library(MathFunctions MathFunctions.cpp)

# 把生成的libMathFunctions.a静态库复制到DESTINATION/bin) 路径下
install (TARGETS MathFunctions DESTINATION bin)
# 把头文件复制到DESTINATION/include路径下
install (FILES MathFunctions.h DESTINATION include)

