#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;

#define DEBUG 

// 这一段写在前面，通过宏来debug
#ifdef DEBUG
// #define debug(format,...) fprintf(stdout,format,##__VA_ARGS__)
#define debug(format,args...) fprintf(stdout, format, ##args) //这和上一句的作用是相同的,##__VA_ARGS__和args都是可变参数，可以没有这个参数
#else
#define debug(format,...) // 定义一个函数宏，没有实现，则非DEBUG模式下debug都不会打出来
#endif

// 用来将错误行数打印
#define SHOW_CODE_LOCATION() cout<<__FILE__<<':'<<__LINE__<<'\n' 

int main(int argc,char ** argv){
	int a = 1;
	debug("a 是 %d\n",a);//ok
	debug("你妹\n");//ok
	// debug(a);//error
	if( 0 != rename("nihao","nimei")){
		cout<<"failed to move file"<<endl;
		SHOW_CODE_LOCATION();
	}
	return 0;
}