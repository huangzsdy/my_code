#include<iostream>
#include<string>

using namespace std;

int changeToUpper(const char * str1){
	string str = str1;
	for(string::iterator iter = str.begin();iter != str.end();iter++){
		*iter = toupper(*iter);
	}
	cout<<"string: "<<str<<endl;;
	return 0;
}

void delUpperWord(string & tmp){
	for(string::iterator iter = tmp.begin();iter != tmp.end();iter++){
		if(isupper(*iter)){
			tmp.erase(iter);
			iter = --iter;
		}
	}

	cout<<"after change: "<<tmp<<endl;
}

int main(int argc,char ** argv){
	string str = "This is an example";
	changeToUpper(str.c_str());
	delUpperWord(str);
	cout<<str;
}