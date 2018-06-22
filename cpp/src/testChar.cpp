#include <iostream> 
#include <cstring> 
#include <string>
#include <typeinfo>
using namespace std;

#define BUF1 ("HELLO WOLRD")
#define BUF2 ("MY NAME")

void t0(){
	char temp1 []= "Computer ";
	char temp2 []= "Dello";
	cout<<"size "<<strncmp(temp1,temp2,1)<<endl;
	char * tmp = strncat(temp1,temp2,3);
	cout<<temp1<<endl<<endl<<endl;
}

void t1(){
	char str[512];
	memset(str,0,512);
	memcpy(str,BUF1,strlen(BUF1));
	cout<<"str = "<<str[0]<<endl;
	memcpy(str + strlen(BUF1),BUF2,strlen(BUF2));
	cout<<"str = "<<str<<endl;
	cout<<"BUF1 = "<<BUF1[0]<<endl;
	cout<<"BUF2 = "<<BUF2<<endl;
}

void t2(){
	int a = 0;
	cout<<"BUF1 type: "<<typeid(int).name()<<endl;
}

void t3(){
	string a = BUF1;
	string b = BUF2;
	string tmp;
	tmp.assign(a.begin(),a.begin() + 3);
	tmp.append(a.substr(a.find("WOL"),10));
	cout<<"tmp "<<tmp<<endl;
}

int main(int argc,char **argv){
	t3();
	return 0;
}
