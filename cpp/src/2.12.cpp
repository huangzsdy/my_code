#include <iostream>
using namespace std;

int find_method_1(const int arr[],int length,int to_find){
	for(int i=0;i<length;i++){
		if(arr[i] == to_find)
			return i;
	}
	return -1;
}

int main(int argc,char **argv){
	int n,tmp;
	int arr[200] = {0};
	while(cin>>n){
		for(int j=0;j<n;j++)
			cin>>arr[j];
		cin>>tmp;
		cout<<find_method_1(arr,n,tmp)<<endl;
	}
}