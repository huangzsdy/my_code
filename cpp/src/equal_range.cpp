#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

void vector_equal_range(int input){
	int tmp[100] = {0,2,4,34,3,123,3,5,6,7,8,1,9};
	vector<int> nums(tmp,tmp+10);
	pair<vector<int>::iterator,vector<int>::iterator> result;
	result = equal_range(nums.begin(),nums.end(),input);
	cout<<"first place: "<<*result.first<<" second place: "<<*result.second<<endl;

}

//三种查找方式
void multimap_find(){
	multimap<int,const char*>mp;
	mp.insert(pair<int,const char*>(1,"hehe"));
	mp.insert(pair<int,const char*>(1,"haha"));
	mp.insert(pair<int,const char*>(2,"err"));
	mp.insert(pair<int,const char*>(3,"goke"));
	mp.insert(pair<int,const char*>(3,"wdc"));
	mp.insert(pair<int,const char*>(2,"azod"));	
	multimap<int,const char*>::iterator it;

	for(it=mp.begin();it!=mp.end();it++){
		cout<<it->first<<"-->"<<it->second<<endl;
	}
	//method 1
	int count = mp.count(3);
	it = mp.find(3);
	for(int i=0;i<count;i++){
		cout<<"first: "<<it->first<<" second: "<<it->second<<endl;
		++it;//因为3肯定是连在一块的
	}
	cout<<"-----"<<endl;
	//method 2
	for(it=mp.lower_bound(3);it!=mp.upper_bound(3);it++){
		cout<<"first: "<<it->first<<" second: "<<it->second<<endl;
	}
	cout<<"-----"<<endl;
	//method 3
	pair<multimap<int,const char*>::iterator,multimap<int,const char*>::iterator> pos;
	for(it = mp.equal_range(3).first;it!=mp.equal_range(3).second;it++){
		cout<<"first: "<<it->first<<" second: "<<it->second<<endl;
	}


	pos = mp.equal_range(3);
	cout<<"pos.second: "<<pos.second->first<<" -->"<<pos.second->second<<endl;
	// for(pos=mp.equal_range(3);pos.first!=pos.second;pos.first++){
	// 	cout<<"pos.second: "<<pos.second->first<<" -->"<<pos.second->second<<endl;
	// 	cout<<"first: "<<pos.first->first<<" second: "<<pos.first->second<<endl;
	// }
	
}

void map_find(){
  map<char,int> mymap;
  pair<map<char,int>::iterator,map<char,int>::iterator> ret;

  mymap['a']=10;
  mymap['b']=20;
  mymap['c']=30;

  ret = mymap.equal_range('b');

  cout << "lower bound points to: ";
  cout << ret.first->first << " => " << ret.first->second << endl;

  cout << "upper bound points to: ";
  cout << ret.second->first << " => " << ret.second->second << endl;

}


int main(int argc,char **argv){
	// vector_equal_range(atoi(argv[1]));
	// multimap_find();
	map_find();
	return 0;
}