#include <iostream>  
#include <vector>  
#include <algorithm>  
#include "boost/function.hpp"  
using namespace std;

bool check_size1(const int x,int sz){
  return x > sz;
}

void check_size2(int x,int & sz){
  sz = 6;
  x += 1;
}

int main(){
  vector<int> v = {10,2,3,4,5,6,7,8,9};
  int n = 3;
  auto new_check_size1 = bind(check_size1,std::placeholders::_1,n);//其中_1，_2这种都是占位符，用来表示对应的第几个参数
  auto it = find_if(v.begin(),v.end(),new_check_size1);//因为n已经在bind中定义好，所以只要一个_1的参数就行。
  cout<<"1 it 的值为:"<<*it<<endl;

  auto new_check_size2 = bind(check_size2,std::placeholders::_1,ref(n));
  it = find_if(v.begin(),v.end(),new_check_size2);
  cout<<"2 it 的值为:"<<*it<<endl;
  return 0;
}