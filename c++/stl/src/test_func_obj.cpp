#include <iostream>
#include <vector>
#include <set>
#include <iterator>
#include <algorithm>

using namespace std;
/*
 * 1.函数对象,可以达到类似静态变量的功能，m_a，每次调用add都会累加
 * 2.generate_n (iter,n,op)，调用n次的op()，返回值赋给iter，且iter++
 * 3.lambda 表达式，[]代表传参的作用域及传参的方式，()代表参数，-> 代表返回值 
 */

class Sort1{
   public:
      Sort1(int a):m_a(a){}
      int  operator () (){
           cout<<"m_a:"<<m_a<<endl;
           add();
           return m_a;
      }
   private:
      void add(){m_a++;}
      int m_a;
};

int main(int argc,char** argv){
  int a[] = {1,2,3,4,5,6,7,8,9,0};
  vector<int>dest(a,a+10);
  cout<<"generate_n 之前:"<<endl;
  for_each(dest.begin(),dest.end(),[](int arg){cout<<arg<<" ";});
  cout<<endl;
  cout<<"generate_n 之后:"<<endl;
  //generate_n(back_inserter(dest),10,Sort1(2));
  back_insert_iterator<vector<int>> b_iter (dest);
  //generate_n(b_iter,10,Sort1(2));
  back_inserter(dest) = 199;//back_inserter是函数，返回dest的back_insert_iterator指针
  for_each(dest.begin(),dest.end(),[](int arg){cout<<arg<<" ";});
  return 0;
}
