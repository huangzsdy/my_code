project(Embedding) #随便起一个工程名称

#boost.python,python头文件路径
include_directories(/home/huangzesang/share/my_env/boost/include /home/software/local/include/python2.7)

link_directories(/home/huangzesang/share/my_env/boost/lib /home/software/local/lib)  #boost.python,python动态链接库路径

add_executable (embedding embedding.cc)  #源文件embedding.cc 生成可执行文件embedding
target_link_libraries(embedding libboost_python.so libpython2.7.so) #可执行文件依赖与这两个库
