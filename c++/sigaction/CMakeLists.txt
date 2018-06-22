project(static_test) #随便起一个工程名称

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

include_directories(/home/software/local/include)

link_directories(/home/software/local/lib)  #boost动态链接库路径

SET(EXECUTABLE_OUTPUT_PATH ../bin) #设置存放可执行文件的路径

add_executable (test1 src/test1.cpp)  # 可执行文件和对应的代码
add_executable (test2 src/test2.cpp)  # 可执行文件和对应的代码
#target_link_libraries(v1) #可执行文件依赖与这两个库

