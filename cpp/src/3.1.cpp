#include <iostream>
#include <stack>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <cstring>

using namespace std;
// string input(100,' ');
// string output(100,' ');
stack<int>S;
char input[100];
char output[100];
// string 类型要先有长度，才能取下标操作

// int main(int argc,char ** argv){
// 	while(cin>>input){
// 		cout<<"input is:"<<input<<" input size is: "<<input.size()<<endl;
// 		for(int i = 0;i<input.size();i++){
// 			if(input[i] == '('){
// 				output[i] = ' ';
// 				S.push(i);
// 				cout<<"input[i] is:"<<input[i]<<" output 1 is: "<<output.length()<<endl;
// 			}

// 			else if (input[i] == ')'){
// 				if(!S.empty()){
// 					output[i] = ' ';
// 					S.pop();
// 				}
// 				else{
// 					output[i] = '?';
// 					cout<<"input[i] is:"<<input[i]<<" "<<output[i]<<" output 3 is: "<<output.length()<<endl;
// 				}
// 				cout<<"input[i] is:"<<input[i]<<" output 2 is: "<<output.length()<<endl;
// 			}
// 			else
// 				output[i] = ' ';
			
// 		}
// 		while(!S.empty()){
// 			output[S.top()] = '$';
// 			S.pop();
// 		}
// 		cout<<"result"<<endl;
// 		cout<<output<<endl;
// 	}
// 	return 0;
// }
int main(int argc,char ** argv){
	while(scanf("%s",input) != EOF){
		for(int i = 0;i < strlen(input) ;i++){
			if(input[i] == '('){
				output[i] = ' ';
				S.push(i);
			}
			else if (input[i] == ')'){
				if(S.empty() == false){
					output[i] = ' ';
					S.pop();
				}
				else
					output[i] = '?';
			}
			else
				output[i] = ' ';
		}
		while(!S.empty()){
			output[S.top()] = '$';
			S.pop();
		}
		cout<<"result"<<endl;
		cout<<output<<endl;
	}
	return 0;
}