#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
using namespace std;

struct Student{
	char no[10];
	string name;
	int age;
	bool operator < (const Student & A) const{
		return strcmp(no,A.no) < 0;
	}
}buf[1000];

int binarySearch(const Student  arr[],int length,string val){
	int start = 0,end = length -1;
	int middle = -1;
	while(start <= end){
		middle = (start + end)/2;
		if(arr[middle].no == val)
			return middle;
		else if(arr[middle].no < val){
			start = middle + 1;
		}
		else
			end = middle - 1;

	}
	return -1;
}

int main(int argc,char**argv){
	int n,input;

	while(cin>>n){
		for(int i=0;i<n;i++){
			cin>>buf[i].no>>buf[i].name>>buf[i].age;
		}
		sort(buf,buf+n);
		cin>>input;
		string number[input];
		for(int k = 0;k<input;k++){
			cin>>number[k];
		}
		for(int j = 0;j<input;j++){
			int index = binarySearch(buf,n,number[j]);
			if(index == -1)
				cout<<"No Answer!"<<endl;
			else
				cout<<buf[index].no<<" "<<buf[index].name<<" "<<buf[index].age<<endl;
		}
	}
}

