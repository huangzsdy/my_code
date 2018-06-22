#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <stdio.h>

using namespace std;
#define N (10)

void char_memcpy(){
	char *p1 = "abcde";
	char *p2 = (char *)malloc(sizeof(char) * N);
	char *p3 = (char *)memcpy(p2,p1,N);
	cout<<"p2: "<<p2<<endl;
	cout<<"p3: "<<p3<<endl;
	free(p2);
	p2 = NULL;
	p3 = NULL;
}

void char_copy(){
	char *s ="Golden Global View";
	char d[20];
	memcpy(d,s+14*sizeof(char),4*sizeof(char));
	if(d[4] == '\t')
		cout<<"same"<<endl;
	cout<<"d: "<<d[4]<<endl;
}

void int_copy(){
	// int arr1[4] = {1,2,3};
	// int arr2[4];
	char arr1[] = "fdfd";
	char arr2[10];
	cout<<"arr2 length: "<<sizeof(arr2)<<endl;
	memcpy(arr2,arr1,sizeof(arr2));
	cout<<"arr2[0] "<<arr2[0]<<endl;
	cout<<"strlen: "<<strlen(arr2)<<endl;
}


int main(int argc,char **argv){
	int i;
	char *p="dfd";
	cout<<"ori i: "<<i<<endl;
	i = reinterpret_cast<int>(p);
	cout<<" re: "<<i<<endl;
	return 0;
}