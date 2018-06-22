#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

/*
* strlen 用来判断字符串长度，参数可以是字符串指针、字符串常量、字符数组
* sizeof 的参数可以有多种
* 如：数组——编译时分配的数组空间大小,如果是一个字符串，则sizeof长度需要加上最后的\0，其余类型根据数组类型*数组长度
* 指针——存储该指针所用的空间大小（存储该指针的地址的长度，是长整型，应该为4）；
* 类型——该类型所占的空间大小；
*/

int main(int argc,char **argv){
	char str1[3] = {'f','w'};
	printf("%d strlen(char str[20])\n", strlen(str1));
	char str2[] = "fdafa";
	printf("%d strlen(char [])\n",strlen(str2));
	char * str3 = "wa";
	printf("%d strlen(char *)\n",strlen(str3));
	char * str4 = new char[1000];
	printf("%d strlen(new char[10])\n",strlen(str4));
	printf("-------------\n");
	printf("%d sizeof char str[20]\n",sizeof(str1));
	printf("%d sizeof char []\n",sizeof(str2));
	printf("%d sizeof char *\n",sizeof(str3));
	printf("%d sizeof new char[1000]\n",sizeof(str4));
	delete str4;
	return 0;
}