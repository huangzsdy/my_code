#include<iostream>
#include<stdlib.h>
#include<set>
using namespace std;

#define random(x) (rand()%x)

int main(int argc,char **argv){
     set <int> arr;
     set<int> ::iterator iter ;
     int i=0;
     while(arr.size() != 10){
	int rand_int = random(99);
        iter = arr.find(rand_int);
        if (iter == arr.end()){
           arr.insert(rand_int);
           cout<<"insert: "<<rand_int<<endl;
	}
     }
     for(iter = arr.begin();iter != arr.end();iter++)
        cout<<*iter<<endl;

     return 0;
     
}
