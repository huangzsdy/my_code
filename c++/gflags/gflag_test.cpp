#include <iostream>
#include <gflags/gflags.h>
/*
** 用glag 控制输入的参数
*/
using namespace std;

DEFINE_string(confPath,"../conf/setup.ini", "program configure file.");
DEFINE_int32(port,9090,"program listen port");
DEFINE_bool(daemon,true,"run daemon mode");

// 检查 参数 port
static bool ValidatePort(const char * flagname,gflags::int32 port){
    if (port >= 36800 && port <= 36888){
        cout<<"params("<<flagname<<")  = "<<port<<" is valid"<<endl;
        return true;
    }
    cout<<"params("<<flagname<<")  = "<<port<<" is invalid"<<endl;
    return false;
}
static const bool validPort = gflags::RegisterFlagValidator(&FLAGS_port,&ValidatePort);

int main(int argc,char ** argv){
    gflags::SetVersionString("0.0.0.0");
    gflags::SetUsageMessage("Usage : ./test1");
    gflags::ParseCommandLineFlags(&argc,&argv,true);

    for(int i = 0;i < argc; i++){
        cout<<"argv["<<i<<"] = "<<argv[i]<<endl;
    }

    cout<<"confPath = " << FLAGS_confPath <<endl;
    cout<<"port = " <<FLAGS_port <<endl;
    if (FLAGS_daemon) {
        cout << "run background ..." << endl;
    }
    else {
        cout << "run foreground ..." << endl;
    }

    cout << "good luck and good bye!" << endl;
    gflags::ShutDownCommandLineFlags();
}

