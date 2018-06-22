#include <iostream>
#include <stack>
#include <cstring>
#include <cstdio>
/*
 * ** 1.因为需要读入空格，所以用gets，cin会跳过空格 
 * ** 2.两个栈，一个存储运算符，一个存储数字，在运算符栈的首尾都有一个“标志运算符 ”，序号为 0 ，且优先级小于其他任何运算符 
 * */
using namespace std;

int mat[][5] = {
	1,0,0,0,0,
	1,0,0,0,0,
	1,0,0,0,0,
	1,1,1,0,0,
	1,1,1,0,0
};

char str[100];
stack<int>op;
stack<double>in;

void getOp(bool & reto,int &retn,int &i){
	if(i == 0 && op.empty() == true){
		reto = true;
		retn = 0;
		return;
	}
	if(str[i] == 0){
		reto = true;
		retn = 0;
		return;
	}
	if(str[i] < '0' || str[i] > '9'){
		reto = true;
		if(str[i] == '+'){
			retn = 1;
		}
		else if(str[i] == '-'){
			retn = 2;
		}
		else if(str[i] == '*'){
			retn = 3;
		}
		else if(str[i] == '/'){
			retn = 4;
		}
		i += 2;
		return;
	}
	else{
		reto = false;
		retn = 0;
		for(;str[i] != ' ' && str[i] != 0;++i){
			retn *= 10;
			retn += str[i] - '0';
		}
		if(str[i] == ' ')
			++i;
		return;
	}
}

int main(){
	while(gets(str)){
		if(str[0] == '0' && str[1] == 0) break;
		while(!op.empty())op.pop();
		while(!in.empty())in.pop();
		int idx = 0;
		int retnum;bool retop;
		while(true){
			getOp(retop,retnum,idx);
			if(retop == false)
				in.push((double)retnum);
			else{
				if(op.empty() == true || mat[retnum][op.top()] == 1){
					op.push(retnum);
				}
				else{
					double tmp;
					while(mat[retnum][op.top()] == 0){
						double second = in.top();
						in.pop();
						double first = in.top();
						in.pop();
						int tmpOperator = op.top();
						op.pop();
						if(tmpOperator == 1) tmp = first + second;
						else if(tmpOperator == 2) tmp = first - second;
						else if(tmpOperator == 3) tmp = first  * second;
						else if(tmpOperator == 4) tmp = first / second;
						in.push(tmp);
					}
					op.push(retnum);
				}
			}
			if(op.size() == 2 && op.top() == 0) break;
		}
		cout<<"结果是:"<<in.top()<<endl;
	}
	return 0;
}
