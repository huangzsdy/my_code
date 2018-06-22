
/*
** set,list,vector,set之间互相转化
**
*/
#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <algorithm>
#include <set>
#include <iterator>

using namespace std;

int main(){
	int arr[5] = {1,3,3,4,4};
	vector<int> v1(arr,arr+5);

	//vector -> set
	set<int> s1(v1.begin(),v1.end());
	copy(s1.begin(),s1.end(),ostream_iterator<int>(cout," "));
	cout<<endl;
	//set -> vector 3 种方法
	vector<int> v2;
	//法1，insert_iterator，不需要指定v2大小
	insert_iterator<vector<int> >in_it(v2,v2.begin());//v2表示要插入的容器，v2.begin()表示插入位置
	copy(s1.begin(),s1.end(),in_it);
	copy(v2.begin(),v2.end(),ostream_iterator<int>(cout," "));
	cout<<endl;	
	//法2，back_inserter,同样不需要指定大小
	vector<int> v3;
	copy(s1.begin(),s1.end(),back_inserter(v3));
	copy(v3.begin(),v3.end(),ostream_iterator<int>(cout," "));
	cout<<endl;
	//法3，直接copy，需要指定v4大小
	vector<int> v4(s1.size());
	copy(s1.begin(),s1.end(),v4.begin());
	copy(v4.begin(),v4.end(),ostream_iterator<int>(cout," "));
	cout<<endl;




	return 0;
}
