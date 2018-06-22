#include<iostream>
#include <dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
using namespace std;
int main()
{
 int status;
// status = mkdir('h',S_IRWXU|S_IRWXG|S_IROTH|S_IXOTH);
 status = mkdir("h",0777);
// cout<<status;
 if (opendir("h") != NULL)
    cout<<"kong"<<endl;
 return 0;
}
