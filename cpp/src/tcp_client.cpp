/******************************
linux socket编程学习
server 端口：0x8888
server 地址: 0.0.0.0
***************************/
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

int main(int argc,char **argv)
{
    int cfd;
    int recbytes;
    int sin_size;
    char buffer[1024] = {0};
    struct sockaddr_in s_add,c_add;
    int portnum = 33232;
    cout<<"client ok!"<<endl;

    cfd = socket(AF_INET,SOCK_STREAM,0);
    if ( -1 == cfd)
    {
        cout<<"socket fail!"<<endl;
        return -1;
    }
    cout<<"socket ok!"<<endl;
    bzero(&s_add,sizeof(struct sockaddr_in));
    s_add.sin_addr.s_addr = inet_addr("127.0.0.1");
    s_add.sin_port = htons(portnum);
    if （-1 == connect(cfd,(struct sockaddr *)(&s_add),sizeof(struct sockaddr));
    {
        cout<< "connect fail !"<<endl;
        return -1;
    }
    cout<<"connection ok!"<<endl;
    if (
