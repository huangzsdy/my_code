/*
** 静态顺序队列
*/

#include <iostream>
#include <cstdlib>

using namespace std;

#define MAXSIZE 10

typedef struct {
	int num;
}DATA;

typedef struct {
	DATA data[MAXSIZE];
	int head;
	int tail;
}SQType;

SQType * SQInit(){
	SQType * s = new SQType;
	if(s == NULL){
		cerr<<"SQInit error!"<<endl;
		return NULL;
	}
	else{
		s->head = s->tail = 0;
		return s;
	}
}

bool SQIsEmpty(SQType * s){
	return s->head == s->tail;
}

bool SQFull(SQType * s){;
	return s->tail == MAXSIZE;
}

void InSQType(SQType * s,DATA data){
	if(s->tail == MAXSIZE){
		cerr<<"SQType is full"<<endl;
	}
	else{
		s->data[s->tail] = data;
		++s->tail;
	}
}

DATA OutSQType(SQType * s){
	if(s->head == s->tail){
		cerr<<"SQType is full"<<endl;
	}
	else{
		DATA tmpData = s->data[s->head];
		s->head++;
		return tmpData;
	}
}

DATA PeekSQType(SQType * s){
	if(SQIsEmpty(s)){
		cerr<<"SQType is empty"<<endl;
		exit(1);
	}
	else{
		return s->data[s->head];
	}
}

int SQLength(SQType * s){
	return s->tail - s->head;
}

void SQFree(SQType * s){
	s->head = s->tail = 0;
	delete s;
}

int main(int argc,char * argv[]){
	SQType * s = SQInit();
	DATA data;
	while(cin>>data.num){
		InSQType(s,data);
	}
	cout<<"SQLength is:"<<SQLength(s)<<endl;
	int count = SQLength(s);
	while(count > 0){
		cout<<"OutSQType:"<<OutSQType(s).num<<endl;
		count--;
	}
	SQFree(s);
	cout<<"SQLength is:"<<SQLength(s)<<endl;
}
