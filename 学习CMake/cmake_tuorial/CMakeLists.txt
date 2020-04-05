#=================== cmake .命令，设置参数========================
cmake_minimum_required (VERSION 2.6)
# 定义Tutorial项目
project (Tutorial)

# The version number.
# 设置配置文件中的参数，根据配置文件自动生成对应的头文件
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)


# does this system provide the log and exp functions?
# 检查系统平台是否提供了exp和log函数，决定是否定义HAVE_EXP和HAVE_LOG宏，从而在cpp中判断是使用系统的还是使用自己的。
include (CheckFunctionExists)
check_function_exists (log HAVE_LOG)
check_function_exists (exp HAVE_EXP)
# 测试代码一定要在TutorialConfig.h的configure_file命令之前。configure_file命令会立即使用CMake中的当前设置配置文件


# configure a header file to pass some of the CMake settings to the source code
# 运行'cmake .'命令时，会根据上面的set命令替换TutorialConfig.h.in配置文件中的参数，然后自动生成TutorialConfig.h头文件
# 两个文件都在PROJECT_SOURCE_DIR目录下
configure_file (
  "${PROJECT_SOURCE_DIR}/TutorialConfig.h.in"
  "${PROJECT_BINARY_DIR}/TutorialConfig.h"
  )

# add the binary tree to the search path for include files so that we will find TutorialConfig.h
# 添加include目录，以便于找到TutorialConfig.h头文件
include_directories("${PROJECT_BINARY_DIR}")

# should we use our own math functions?
# USE_MYMATH是一个布尔值（其实时一个宏），替换TutorialConfig.h.in中的USE_MYMATH参数
# ON表示True，OFF表示False。下面是默认设置
option (USE_MYMATH 
        "Use tutorial provided math implementation" ON)

# 根据USE_MYMATH，是否使用自己库
if (USE_MYMATH)
    # 添加include目录，以便于找到MathFunctions.h头文件
    include_directories ("${PROJECT_SOURCE_DIR}/MathFunctions")
    # 增加子目录MathFunctions，以便于找到libMathFunctions.a库文件
    add_subdirectory (MathFunctions)
    # 把MathFunctions目录追加到EXTRA_LIBS变量中（EXTRA_LIBS类似于环境变量）
    set (EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
endif (USE_MYMATH)
#=============================================================================


#======================= make命令，编译和链接 ===================================
# 生成Tutorial项目的可执行文件
add_executable(Tutorial tutorial.cpp)
# 在Tutorial项目的链接阶段，需要使用到EXTRA_LIBS中的文件，例如libMathFunctions.a库
target_link_libraries (Tutorial ${EXTRA_LIBS})
#==========================================================


#======================== make install命令，复制和安装==========================
# DESTINATION在这里是一个安装路径。在unix系统中指向 /usr/local， 在windows上c:/Program Files/${PROJECT_NAME}
# 也可以通过设置CMAKE_INSTALL_PREFIX这个变量来设置安装的路径，那么安装位置将指向你所指定的目录
# add the install targets
# 把生成的Tutorial可执行文件，复制到DESTINATION/bin目录下
install (TARGETS Tutorial DESTINATION bin)
# 把头文件TutorialConfig.h，复制到DESTINATION/include目录下
install (FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h" DESTINATION include)
# 注意上边install的第一个参数和第三个参数：
# 第一个参数TARGETS：包含六种形式：ARCHIVE, LIBRARY, RUNTIME, OBJECTS, FRAMEWORK,  BUNDLE。注意Mathfunction安装的是LIBRARY，而根目录下的可执行文件是RUNTIME类型。 FILE将给定的文件复制到指定目录。如果没有给定权限参数，则由该表单安装的文件默认为OWNER_WRITE、OWNER_READ、GROUP_READ和WORLD_READ。
# 第三个参数DESTINATION：TARGETS和FILE可指定为相对目录和绝对目录，DESTINATION在这里是一个相对路径。
#==========================================================================


#========================== ctest命令，运行测试用例=================================
include(CTest)

# does the application run
# 验证应用程序是否正常运行，没有发生崩溃，并且返回值是0。这是CTest测试的基本形式
add_test (TutorialRuns Tutorial 25)

# 下面几个测试都使用PASS_REGULAR_EXPRESSION测试属性来验证测试的输出是否包含特定的字符串。
# does it sqrt of 25
add_test (TutorialComp25 Tutorial 25)
set_tests_properties (TutorialComp25 PROPERTIES PASS_REGULAR_EXPRESSION "25 is 5")
# does it handle negative numbers
add_test (TutorialNegative Tutorial -25)
set_tests_properties (TutorialNegative PROPERTIES PASS_REGULAR_EXPRESSION "-25 is 0")
# does it handle small numbers
add_test (TutorialSmall Tutorial 0.0001)
set_tests_properties (TutorialSmall PROPERTIES PASS_REGULAR_EXPRESSION "0.0001 is 0.01")
# does the usage message work?
add_test (TutorialUsage Tutorial)
set_tests_properties (TutorialUsage PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number")

# 如果您想要添加许多测试来测试不同的输入值，您可以考虑创建如下的宏(相当于函数):
#define a macro to simplify adding tests, then use it
macro (do_test arg result)
  add_test (TutorialComp${arg} Tutorial ${arg})
  set_tests_properties (TutorialComp${arg} PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endmacro (do_test)
# 使用上面定义的宏来添加测试用例
# do a bunch of result based tests
do_test (81 "81 is 9")
do_test (-1 "-1 is 0")
#=========================================================================




