#include <iostream>
#include <cstdlib>
using namespace std;

#define MAXSIZE 10

typedef struct{
	int num;
}DATA;

typedef struct stack{
	DATA data[MAXSIZE];
	int count;
}StackType;


StackType * STInit(){
	StackType * s = new StackType;
	if(!s){
		cerr<<"STInit error!!"<<endl;
		return NULL;
	}
	s->count = 0;
	return s;
}

bool STIsEmpty(StackType * s){
	if(s->count == 0){
		return true;
	}
	else
		return false;
}

bool STIsFull(StackType * s){
	if(s->count == MAXSIZE)
		return true;
	else
		return false;
}

void STClear(StackType * s){
	if(s == NULL){
		cout<<"stack is empty"<<endl;
		return;
	}
	else{
		s->count = 0;
		delete s;
	}
}

void PushST(StackType * s,DATA data){
	if(s->count == MAXSIZE){
		cout<<"stack is full"<<endl;
	}
	else{
		s->data[s->count] = data;
		s->count++;
	}
}

DATA PopST(StackType * s){
	if(s->count <= 0){
		cout<<"stack is empty,can not pop"<<endl;
		exit(-1);
	}
	else{
		DATA tmpData = s->data[s->count-1];
		s->count--;
		return tmpData;
	}
}

DATA PeekST(StackType * s){
	if(s->count <= 0){
		cout<<"stack is empty!"<<endl;
		exit(-1);
	}
	else{
		DATA tmpData = s->data[s->count-1];
		return tmpData;
	}
}

int main(int argc,char * argv[]){
	StackType * s = STInit();
	DATA data;
	int input;
	cout<<"初始化后，栈的长度为:"<<s->count<<endl;

	while(cin>>input){
		data.num = input;
		PushST(s,data);
	}
	cout<<"判断栈是否为空?"<<STIsEmpty(s)<<endl;
	cout<<"判断栈是否已满"<<STIsFull(s)<<endl;

	cout<<"取出栈的第一个元素:"<<PeekST(s).num<<endl;
	while(s->count > 0){
		data = PopST(s);
		cout<<"栈中有"<<s->count+1<<"个数据，分别是:"<<data.num<<endl;
	}
	cout<<"释放栈中的元素"<<endl;
	STClear(s);
	cout<<"栈中元素个数为:"<<s->count<<endl;
	
	return 0;
}