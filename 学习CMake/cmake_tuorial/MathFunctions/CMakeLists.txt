#======================== 文件生成器 =============================
# first we add the executable that generates the table
# 使用MakeTable.cpp生成MakeTable可执行文件
add_executable(MakeTable MakeTable.cpp)
 
# add the command to generate the source code
# 添加一个自定义命令来指定通过运行MakeTable来生成平方根表(Table.h)
add_custom_command (
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Table.h
  COMMAND MakeTable ${CMAKE_CURRENT_BINARY_DIR}/Table.h  #相当于执行MakeTable并传入参数${CMAKE_CURRENT_BINARY_DIR}/Table.h
  DEPENDS MakeTable
  )

# add the binary tree directory to the search path for include files
# 添加Table.h的包含路径（因为生成的Table.h表在二进制目录中）
include_directories( ${CMAKE_CURRENT_BINARY_DIR} )
#===========================================================


# 使用MathFunctions.cpp源文件(和Table.h文件)，构建MathFunctions库，生成libMathFunctions.a静态库文件
# 该静态库自己定义了mysqrt函数，用以替代系统中math.h的sqrt函数
add_library(MathFunctions MathFunctions.cpp ${CMAKE_CURRENT_BINARY_DIR}/Table.h)

# 把生成的libMathFunctions.a静态库复制到DESTINATION/bin) 路径下
install (TARGETS MathFunctions DESTINATION bin)
# 把头文件复制到DESTINATION/include路径下
install (FILES MathFunctions.h DESTINATION include)

