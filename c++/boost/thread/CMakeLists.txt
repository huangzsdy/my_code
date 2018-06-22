project(thread_test) #随便起一个工程名称

include_directories(/home/huangzesang/share/my_env/boost/include)

link_directories(/home/huangzesang/share/my_env/boost/lib)  #boost动态链接库路径

SET(EXECUTABLE_OUTPUT_PATH /home/huangzesang/share/learning/my_code/c++/boost/thread/bin) #设置存放可执行文件的路径

add_compile_options(-std=c++11)

add_executable (thread_test1 thread_test1.cpp)  # 可执行文件和对应的代码
target_link_libraries(thread_test1  libboost_system.so libboost_thread.so) #可执行文件依赖与这两个库

add_executable(thread_test2 thread_test2.cpp)
target_link_libraries(thread_test2 libboost_system.so libboost_thread.so)

add_executable(thread_test3 thread_test3.cpp)
target_link_libraries(thread_test3 libboost_system.so libboost_thread.so)

add_executable(thread_test4 thread_test4.cpp)
target_link_libraries(thread_test4 libboost_system.so libboost_thread.so)

