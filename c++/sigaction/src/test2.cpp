#include <csignal>
#include <iostream>
#include <unistd.h>
using namespace std;
/*
1.参考链接:http://blog.csdn.net/guoping16/article/details/6583957
*/
void signal_handler(int signal){
	switch(signal){
		case SIGHUP:
			cout<<"Received 1 "<<SIGHUP<<endl;
			break;
		case SIGINT://Ctrl + c
			cout<<"Received 2 "<<SIGINT<<endl;
			exit(signal);
			break;
	}
}

int main(){
    struct sigaction sa;
    // Setup the handler
    sa.sa_handler = &signal_handler;//绑定处理函数，当收到SIGINT或SIGHUP信号时，有不同的处理
    // Restart the system call, if at all possible
    sa.sa_flags = SA_RESTART;
    // Block every signal during the handler
    sigfillset(&sa.sa_mask);
    // Intercept SIGHUP and SIGINT
    if (sigaction(SIGHUP, &sa, NULL) == -1) {
      cout << "Cannot install SIGHUP handler."<<endl;
    }
    if (sigaction(SIGINT, &sa, NULL) == -1) {
      cout << "Cannot install SIGINT handler."<<endl;
    }	

    while(1){
    	cout<<"Going to sleep..."<<endl;
    	sleep(1);
    }
	return 0;
}