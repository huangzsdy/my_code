#include <iostream>
using namespace std;
//参考链接:https://www.cnblogs.com/wangj08/p/3472486.html
/*
1.类静态成员变量，需要在类体外定义（不管是不是private的）
2.类静态函数不能访问非静态成员
3.类非静态函数可以访问静态成员,也可以访问静态函数
4.静态数据成员是静态存储的，必须要初始化。
5.静态成员函数不能直接调用非静态成员，除非传入类引用实现调用该引用的非静态成员。
6.静态成员的初始化要在实现中进行，不能在头文件中
*/
class Point{
public:
	void output(){cout<<x<<" "<<y<<endl;init();}
	static void init(){
		cout<<"x ="<<x<<" y = "<<y<<endl;
		x = 0;y = 0;
	}
private:
	static int x;
	static int y;
};
int Point::x = -1;
int Point::y = -1;//不能在main函数里初始化
int main(){
  Point::init();
  Point::init();
  Point p;
  p.output();
  return 0;
}
