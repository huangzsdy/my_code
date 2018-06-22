#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>

using namespace std;

struct Student{
	string name;
	int age;
	int score;
	bool operator < (const Student & b) const{
		if(score != b.score)
			return score < b.score;
		if(name != b.name)
			return name < b.name;
		return age < b.age;
	}
};

int main(int argc,char **argv){
	Student arr[10];
	int age,score;
	string name;
	int n;
	cout<<"input n "<<endl;
	while(cin>>n){
		for(int k=0;k<n;k++)
			cin>>arr[k].name>>arr[k].age>>arr[k].score;
		sort(arr,arr+n);
		for(int j=0;j<n;j++)
			cout<<"name: "<<arr[j].name<<" age: "<<arr[j].age<<" score: "<<arr[j].score<<endl;
	}
	
	return 0;
}