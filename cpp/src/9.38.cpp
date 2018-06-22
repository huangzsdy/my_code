#include<iostream>
#include<string>

using namespace std;;


const string numerics = "1234567890";
const string letters = "abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ";

string find1(string str){
	int pos = 0;
	string res;
	while((pos = str.find_first_of(numerics,pos)) != string::npos){
		res.push_back(str[pos]);
		++pos;
	}

	return res;
}
string find2(string str){
	int pos = 0;
	string res;
	while((pos = str.find_first_of(letters,pos)) != string::npos){
		res.push_back(str[pos]);
		++pos;
	}
	return res;
}

int main(int argc,char ** argv){
	string test = "ab2c3d72R1dw2";
	cout<<"method 1 "<<find1(test)<<endl;
	cout<<"method 2 "<<find2(test)<<endl;
	return 0;
}