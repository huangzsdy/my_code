#include <iostream>
#include <string>
#include <unistd.h>
#include <csignal>

using namespace std;

void signal_handler(int signum){
	cout<<"Interrupt signal ("<<signum<<") received"<<endl;
	exit(signum);
}

int main(){
	signal(SIGINT,signal_handler);
	int i = 0;
	while(++i){
		cout<<"Sleep.."<<endl;
		sleep(1);
	}
	return 0;
}