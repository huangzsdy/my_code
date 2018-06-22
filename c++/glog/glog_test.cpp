#include <glog/logging.h>

int main(int argc,char* argv[])
{
//用GFLAGS 来读取参数，其中 -log_dir=要存放日志的文件夹
    ::google::InitGoogleLogging(argv[0]);  // 初始化 glog
    ::gflags::ParseCommandLineFlags(&argc, &argv, true);  // 初始化 gflags
    LOG(INFO) << "Hello, GOOGLE!"<<"yeye";  // INFO 级别的日志
    LOG(ERROR) << "ERROR, GOOGLE!";  // ERROR 级别的日志
//    LOG(FATAL) << "FATAL, GOOGLE!";  // FATAL 级别的日志

//CHECK 使用这些宏需要注意类型一致，如果出现类型不一致的，可使用static_cast转换
    int a =  1;
    CHECK_EQ(a,1)<<"1 等于"; //CHECK_EQ 等于
    CHECK_NE(a,2)<<"1 不等于"; //CHECK_NE 不等于
    CHECK_LE(a,4)<<"1 小于等于"; //CHECK_LE 小于等于
    CHECK_GE(a,0)<<"1 大于等于"; //CHECK_GE 大于等于
    CHECK_LT(a,2)<<"1 小于"; //CHECK_LT 小于
    CHECK_GT(a,2)<<"1 大于"; //CHECK_GT 大于
    return 0;
}
