#include <iostream>
#include <set>
#include <algorithm>
#include <iterator>

using namespace std;


void print(int to_print){
	cout<<to_print<<endl;
}

int main(){
	int a[4] = {1,2,2,3};
	//从小到大
	set<int,less<int>> s1(a,a+4);
	for_each(s1.begin(),s1.end(),print);

	cout<<(s1.count(1)?"true":"false")<<endl;
	//lower_bound,upper_bound
	cout<<*s1.lower_bound(2)<<endl;//返回一个迭代器，指向键值>= key的第一个元素。
	cout<<*s1.upper_bound(2)<<endl;//返回一个迭代器，指向键值>= key的第一个元素。
	//distance
	cout<<(distance(s1.begin(),s1.lower_bound(2)) + 1)<<endl;//distance 距离,返回两iterator 距离
	cout<<(distance(s1.begin(),s1.upper_bound(2)) + 1)<<endl;
	cout<<endl;

	int b[2] = {101,1002};
	s1.insert(b,b+2);
	for_each(s1.begin(),s1.end(),print);
	return 0;
}