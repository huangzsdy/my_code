#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <string>

using namespace std;

//map 的定义是
//template < class Key, class T, class Compare = less<Key>,  
//           class Allocator = allocator<pair<const Key,T> > > class map;
//Compare 是一个函数对象，一般就是重载了operator ()并且有无参构造函数的class或struct,比如以下的Util和Sort，但都是按Key排序的

struct Util{
	Util(){}
	Util(int a):a_(a){};
	//可以这么做，但不建议这么做，没必要弄成静态函数
	static void print(pair<const int,string>to_print){
		cout<<to_print.first<<" "<<to_print.second<<endl;
	};

	// 根据string的长度
	bool operator ()(const string &A,const string& B){
		if(A.length() < B.length())
			return true;
		else
			return false;
	};
	int a_;
};

// 根据第一个char 的大小递增
struct Sort{
	bool operator ()(const string &A,const string &B){
		return A[0] < B[0];
	}
};

// 根据Util.a_ 递减
bool comp_by_value(const pair<string,Util> &A,const pair<string,Util> &B){
	return A.second.a_ > B.second.a_;
}

ostream& operator <<(ostream & out,const pair<int,string> p){
	return out<<p.first<<" "<<p.second<<endl;
}


int main(){
	map<int,string> map1;
	map1.insert(pair<int,string>(1,"A"));
	map1.insert(pair<int,string>(2,"B"));

	//判断是否插入
	pair<map<int,string>::iterator,bool> isInsert = map1.insert(pair<int,string>(2,"C"));//insert 方式，如果key存在则无法插入
	cout<<"1 insert success? "<<(isInsert.second ? "true":"false")<<endl;
	for_each(map1.begin(),map1.end(),Util::print);

	map1[2] = "D";
	for_each(map1.begin(),map1.end(),Util::print);//这种方式可以insert
	cout<<"-"<<endl;

	//find 的三种方法
	//1.count
	int count = map1.count(4);
	cout<<count<<endl;

	//2.find
	cout<<(map1.find(2) == map1.end() ? "true":"false")<<endl;

	//3.equal_range
	pair<map<int,string>::iterator,map<int,string>::iterator> mapPair;
	mapPair = map1.equal_range(4);
	if(mapPair.first == mapPair.second)
		cout<<"do not found"<<endl;
	cout<<"--"<<endl;

	//遍历
	map<int,string>::iterator iter;
	for(iter = map1.begin();iter != map1.end();++iter)
		cout<<iter->first<<" "<<iter->second<<endl;

	//cout 的重载
	map<int,string>::reverse_iterator rIter;
	for(rIter = map1.rbegin();rIter != map1.rend();++rIter)
		cout<<*rIter;


	//删除
	int isRemove = map1.erase(1);
	for_each(map1.begin(),map1.end(),Util::print);
	cout<<isRemove<<endl;
	cout<<"---"<<endl;

	Util u1(100),u2(200);
	// map<int,Util,Util> map2; //这个也行，但一般Sort独立出来
	map<string,Util,Sort> map2;
	map2["g2"] = u1;
	map2["e"] = u2;
	// map2.insert(pair<int,Util>(1,u2));
	// map2.insert(pair<int,Util>(2,u1));
	map<string,Util>::iterator	mIter = map2.begin();
	for(;mIter != map2.end();++mIter)
		cout<<mIter->first<<" "<<(mIter->second).a_<<endl;
	cout<<"----"<<endl;

	// 按value排序，借助vector
	vector<pair<string,Util>> int_Util_vector(map2.begin(),map2.end());
	sort(int_Util_vector.begin(),int_Util_vector.begin(),comp_by_value);
	for(int i = 0;i < int_Util_vector.size();++i)
		cout<<int_Util_vector[i].second.a_<<endl;

	return 0;
}