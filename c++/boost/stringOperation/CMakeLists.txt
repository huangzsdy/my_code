project(thread_test) #随便起一个工程名称

include_directories(/home/huangzesang/share/my_env/boost/include)

link_directories(/home/huangzesang/share/my_env/boost/lib)  #boost动态链接库路径

SET(OUTPUT_PATH /home/huangzesang/share/learning/my_code/c++/boost)
SET(EXECUTABLE_OUTPUT_PATH ${OUTPUT_PATH}/stringOperation/bin) #设置存放可执行文件的路径

add_executable (string_test1 string_test1.cpp)  # 可执行文件和对应的代码
target_link_libraries(string_test1 libboost_regex.so libboost_system.so libboost_thread.so) #可执行文件依赖与这两个库



