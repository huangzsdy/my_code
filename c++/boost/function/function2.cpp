#include <iostream>
#include <boost/function.hpp>
#include <vector>

using namespace std;

void print_new_value(int i){
	cout<<"The value has been updated and is now "<<i<<endl;
}

void interested_in_the_change(int i){
	cout<<"Ah,the value has changed"<<endl;
}

class knows_the_previous_value{
private:
	int last_value_;//函数对象可以保留last_value_
public:
	void operator()(int i){
		static bool first_time = true;
		if(first_time){
			first_time = false;
			last_value_ = i;
			cout<<"This is the first change of value,so I don't konw the previous one."<<endl;
			return;
		}
		cout<<"Previous value was "<<last_value_<<endl;
		last_value_ = i;
	}
};

class notifier{
private:
	typedef boost::function<void(int)> function_type;//可以用于函数对象
	// typedef void (*function_type)(int);//函数指针只能用于函数，无法用于函数对象
	vector<function_type> vec_;
	int value_;
public:
	// void add_observer(function_type t){//如果是用boost::function，则要用泛型
	// 	vec_.push_back(t);
	// }
	template <typename T> void add_observer(T t){
		vec_.push_back(function_type(t));//可以用函数指针初始化，也可以用函数对象初始化
	}
	void change_value(int i){
		value_ = i;
		for(auto& func:vec_){
			func(value_);
			//(*func)(value_);//函数指针的写法。
		}
	}
};


int main(int argc,char ** argv){
	notifier n;
	n.add_observer(&print_new_value);//函数的地址或者函数对象都可以初始化boost::function
	n.add_observer(&interested_in_the_change);
	n.add_observer(knows_the_previous_value());
	n.change_value(42);
	cout<<endl;
	n.change_value(30);
	cout<<endl;
	n.change_value(12);
	return 0;
}