#include <iostream>
#include <string>
#include <cstring>
using namespace std;


// void input2string(){
// 	string str1,str2;
// 	string tmp;
// 	while(1){

// 	}
// }

void test(){
	char tmp[10];
	int a;
	for (int i = 0; i < 2; ++i)
	{
	cin.get(tmp,10,'\n');
		cin.ignore(1024,'\n');
		cin>>a;
		cout<<"tmp is:"<<tmp<<endl;
		cout<<"a is:"<<a<<endl;
		memset(tmp,0,sizeof(tmp));
	}
}

void input2char(){
	char arr[10];
	char tmp;
	while(1){
		memset(arr,0,sizeof(arr));
		for(int i = 0;i<10;i++){
			tmp = cin.get();
			if(tmp == '\n')
				continue;
			else
				arr[i] = tmp;
		}
		cin.ignore(1024,'\n');
		cout<<"ignore"<<endl;
		int a ;
		cin>>a;
		cout<<"arr is:"<<arr<<" a is:"<<a<<endl;

	}
}
int main(){
	// input2string();
	// input2char();
	test();
}