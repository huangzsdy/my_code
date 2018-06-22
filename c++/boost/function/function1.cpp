#include <iostream>
#include <boost/function.hpp>
#include <string>

using namespace std;
int fsum(int i,int j){
	return i + j;
}

class Person{
public:
	void operator ()(string name,int age){
		cout<<name<<" "<<age<<endl;
	}
};

class Car{
public:
	inline void info(int i){
		cout<<"info = "<<i<<endl;
	}
};

int main(int argc,char ** argv){
	//1.普通函数
	boost::function<int(int,int)>func1;
	func1 = &fsum;
	cout<<"4 + 5 = "<<func1(4,5)<<endl;

	//2.函数对象
	boost::function<void(string,int)>func2;
	Person person;
	func2 = person;
	func2("myname",40);

	//3.成员函数
	boost::function<void(Car*,int)>func3;
	func3 = &Car::info;
	Car car;
	func3(&car,25);

	//4.空函数
	boost::function<int(int,int)> func4;
	assert(func4.empty());
	assert(!func1.empty());
	func1.clear();
	assert(func1.empty());
	try{
		func1(1,5);
	}
	catch(exception& e){
		cout<<e.what()<<endl;
	}
	return 0;
}