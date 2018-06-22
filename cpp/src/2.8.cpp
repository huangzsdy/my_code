#include <iostream>
using namespace std;

int main(int argc,char ** argv){
	int n = 0;
	int tmp ;
	while(cin>>n&&n!=0){
		int count[101] = {0};
		for(int i=0;i<n;i++){
			cin>>tmp;
			count[tmp]++;
		}
		cin>>tmp;
		cout<<"----"<<count[tmp]<<endl;
	}	
}