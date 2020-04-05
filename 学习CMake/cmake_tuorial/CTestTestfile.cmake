# CMake generated Testfile for 
# Source directory: /home/zhangth/github/DesignPattern/学习CMake/cmake_tuorial
# Build directory: /home/zhangth/github/DesignPattern/学习CMake/cmake_tuorial
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(TutorialRuns "Tutorial" "25")
add_test(TutorialComp25 "Tutorial" "25")
set_tests_properties(TutorialComp25 PROPERTIES  PASS_REGULAR_EXPRESSION "25 is 5")
add_test(TutorialNegative "Tutorial" "-25")
set_tests_properties(TutorialNegative PROPERTIES  PASS_REGULAR_EXPRESSION "-25 is 0")
add_test(TutorialSmall "Tutorial" "0.0001")
set_tests_properties(TutorialSmall PROPERTIES  PASS_REGULAR_EXPRESSION "0.0001 is 0.01")
add_test(TutorialUsage "Tutorial")
set_tests_properties(TutorialUsage PROPERTIES  PASS_REGULAR_EXPRESSION "Usage:.*number")
add_test(TutorialComp81 "Tutorial" "81")
set_tests_properties(TutorialComp81 PROPERTIES  PASS_REGULAR_EXPRESSION "81 is 9")
add_test(TutorialComp-1 "Tutorial" "-1")
set_tests_properties(TutorialComp-1 PROPERTIES  PASS_REGULAR_EXPRESSION "-1 is 0")
subdirs(MathFunctions)
