/******************************
linux socket编程学习
server 端口：0x8888
server 地址: 0.0.0.0
***************************/
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <linux/in.h>


using namespace std;

int main(int argc,char*argv[])
{
    int sfp,nfp;
    struct sockaddr_in s_add,c_add;
    int sin_size;
    unsigned short port = 12345;
    cout<<"this is a tcp_server"<<endl;
    sfp = socket(AF_INET,SOCK_STREAM,0);
    if (-1 == sfp)
    {
        cout<<"socket fail !\r";
        return -1;
    }
    cout<<"socket ok!\r"<<endl;
    /*填充服务器端口地址信息，以便下面用此地址和端口监听*/
    bzero(&s_add,sizeof(struct sockaddr_in));
    s_add.sin_family = AF_INET;
    s_add.sin_addr.s_addr = htonl(INADDR_ANY);//此处地址为全零，即接受所有地址
    s_add.sin_port = htons(port);
    /*使用bind进行相应的端口*/
    if(-1 == bind(sfp,(struct sockaddr *)(&s_add), sizeof(struct sockaddr)))
    {
        cout<<"bind failed !"<<endl;
    }
    cout<<"bind ok !"<<endl;
    if(-1 == listen(sfp,5))
    {
        cout<<"listen fail !"<<endl;
        return -1;
    }
    cout<<"listen ok !"<<endl;
    while(true)
    {
        sin_size = sizeof(struct sockaddr_in);
        /* accept服务端使用函数，调用时即进入阻塞状态，等待用户进行连接，在没有客户端进行连接时，程序停止在此处， 
   不会看到后面的打印，当有客户端进行连接时，程序马上执行一次，然后再次循环到此处继续等待。 
   此处accept的第二个参数用于获取客户端的端口和地址信息。 
    */  
        nfp =accept(sfp,(struct socketaddr *)(&c_add),&sin_size);
        if(-1 == nfp)
        {
            cout<<"accept fail !";
            return -1;
        }
        cout<<"accept ok !"<<endl;
        if(-1 == write(nfp,"hello,welcom"))
        {
            cout<<"write fail !"<<endl;
            return -1;
        }
        cout<<"write ok!"<<endl;
        close(nfp);
    }
}