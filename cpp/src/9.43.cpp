#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main(int argc,char **argv){
	string tmp;
	stack<char> sexp;
	cout<<"Enter a expression"<<endl;
	cin>>tmp;
	string::iterator iter =  tmp.begin();
	while(iter != tmp.end()){
		if(*iter != ')'){
			sexp.push(*iter);
			cout<<*iter<<endl;
		}
		else{
			cout<<"there"<<endl;
			while(sexp.top() != '(' && !sexp.empty()){
				cout<<"pop : "<<sexp.top()<<endl;
				sexp.pop();
			}
			if(sexp.empty()){
				cout<<" no value in stack"<<endl;
			}
			else{
				cout<<"pop ( finally "<<sexp.top()<<endl;
				sexp.pop();
			}
		}
		++iter;
	}
	cout<<"size of stack "<<sexp.size()<<endl;
	return 0;
}