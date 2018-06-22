 #include<iostream>
 using namespace std;

/*
 * 以下代码结构两次输出class of a，一次是在test函数内，一次是s调用。test内的a分配在栈上，函数结束后应该就销毁了，为什么s还能调用fun。原来类中的成员数据和函数是存放在不同位置的。C++类的方法存放在"程序代码区"，而类中的数据成员（对象数据成员）存放在类的实例对象中，即该成员数据存放在堆或栈中。s指向对象的成员数据已销毁，而类的方法还在。
 *
 * 若将上面代码第8行改为：cout<<"class of a:"<<this->num<<endl，则因为类的数据成员num已经销毁，所以会打出错误值
 * 
 */
  class A
  {
  public:
      void fun()
      {
          cout<<"class of a:"<<endl;
      }
      int num;
  };
   A* test()
  {
     A*p;
     A a;
     a.num=11;
     p=&a;
 p->fun();
 return p;
  }
 int main()
 {
 A*s=test();
 s->fun();
 return 0;
 }
