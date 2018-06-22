#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
using namespace std;

#define MAXLEN 10

typedef struct {
	int age;
	char name[100];
}DATA;

typedef struct {
	DATA ListDATA[MAXLEN];
	int ListLength ;
}SLType;


void SLinit(SLType * SL){
	SL->ListLength = 0;
	cout<<"init SLType success!"<<endl;
}

int SLLength(SLType * SL){
	return SL->ListLength;
}

int SLInsert(SLType * SL,int n,DATA data){
	if(SL->ListLength == MAXLEN){
		cerr<<"SLType is full,can not insert"<<endl;
		return -1;
	}
	if(n < 0||n > SL->ListLength - 1){
		cerr<<"insert wrong place"<<endl;
		return -1;
	}
	for(int i=SL->ListLength;i >= n;i--){
		SL->ListDATA[i + 1] = SL->ListDATA[i];
	}
	SL->ListDATA[n] = data;
	SL->ListLength++;
	return 1;
}

int SLAdd(SLType * SL,DATA data){
	if(SL->ListLength >= MAXLEN){
		cerr<<"SLType is full,can not add"<<endl;
		return -1;
	}
	SL->ListDATA[SL->ListLength] = data;
	SL->ListLength++;
	return 1;
}

int SLDelete(SLType * SL,int n){
	int i = 0;
	if(n < 0||n > SL->ListLength - 1){
		cerr<<"delete wrong place"<<endl;
		return -1;
	}
	for(i=n + 1;i < SL->ListLength;i++)
		SL->ListDATA[i - 1] = SL->ListDATA[i];
	SL->ListLength--;
	return 1;
}

DATA * SLFindByNum(SLType * SL,int n){
	if(n < 0 || n > SL->ListLength - 1){
		cerr<<"find wrong place: "<<n<<endl;
		return NULL;
	}
	return &(SL->ListDATA[n]);
}

int SLFindByCont(SLType * SL,char *name){
	for(int i = 0;i < SL->ListLength;i++){
		if(strcmp((SL->ListDATA[i]).name,name) == 0)
			return i;
	}
	return -1;
}

int SLAll(SLType * SL){
	if(SL->ListLength == 0){
		cout<<"SL has no DATA"<<endl;
		return -1;
	}
	for(int i = 0;i < SL->ListLength;i++){
		cout<<i<<" nd DATA is: "<<SL->ListDATA[i].name<<endl;
	}
	return 0;
}

int main(int argc,char *argv[]){
	int age(0),i(0);
	SLType SL;
	DATA data;
	DATA * p;
	char name[10];
	SLinit(&SL);
	cout<<"please input some DATA"<<endl;
	while(cin>>data.name){
		cin>>data.age;
		cout<<"data.name:"<<data.name<<endl;
		cout<<"data.age: "<<data.age<<endl;
		//exit(0);
		if(!SLAdd(&SL,data)){
			cerr<<"insert error"<<endl;
			return -1;
		}
		cout<<"data is:"<<data.name<<" "<<data.age<<endl;
		memset(&(data),0,sizeof(data));
		cout<<"data is:"<<data.name<<" "<<data.age<<endl;		
	}
	cin.clear();
	cout<<"所有节点内容为"<<endl;
	SLAll(&SL);
	cout<<"请输入要取出的节点序号"<<endl;
	cin>>i;
	p=SLFindByNum(&SL,i);
	if(p){
		cout<<p->name<<" "<<p->age<<endl;
	}
	SLDelete(&SL,i);
	cout<<"请输入要匹配的data.name"<<endl;
	cin>>name;
	cout<<"name: "<<name[9]<<endl;
	int index = SLFindByCont(&SL,name);
	if (index != -1)
		cout<<"SLFindByCont find "<<name<<" index is:"<<index<<endl;
	
	SLAll(&SL);
}
