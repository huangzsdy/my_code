project(function_test) #随便起一个工程名称

include(CheckCXXCompilerFlag) # g++ version may not support c++11
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
     message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()
#add_compile_options(-std=c++11) #at least cmake 3.0

#boost.python,python头文件路径
include_directories(/home/huangzesang/share/my_env/boost/include /home/software/local/include/python2.7)
SET(EXECUTABLE_OUTPUT_PATH /home/huangzesang/share/learning/my_code/c++/boost/function/bin) #设置存放可执行文件的路径

link_directories(/home/huangzesang/share/my_env/boost/lib /home/software/local/lib)  #boost.python,python动态链接库路径

add_executable (function1 function1.cpp) 
add_executable (function2 function2.cpp)  #源文件生成可执行文件
add_executable (function3 function3.cpp)
# target_link_libraries(function1 libboost_function.so libpython2.7.so) #可执行文件依赖与这两个库
