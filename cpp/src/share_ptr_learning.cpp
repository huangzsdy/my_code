#include <iostream>
#include <memory>
using namespace std;

class Example{
public:
	Example(int e):e(e){
		cout<<"Example Construct..."<<endl;
	}
	~Example(){
		cout<<"Example Destruct..."<<endl;
	}
	int e;
};

int main(int argc,char ** argv){

	//初始化shared_ptr会增加它的引用计数
	shared_ptr<Example>pInt(new Example(2));
	cout<<(*pInt).e<<endl;
	cout<<"pInt 引用计数:"<<pInt.use_count()<<endl;
	shared_ptr<Example>pInt2 = pInt;
	cout<<"pInt 引用计数:"<<pInt.use_count()<<endl;
	cout<<"pInt2 引用计数:"<<pInt2.use_count()<<endl;

	//make_shared时模板类，参数必须与所指类型的某个构造函数相匹配
	shared_ptr<Example>pInt3  = make_shared<Example>(3);
	cout<<"1 pInt3 引用计数:"<<pInt3.use_count()<<endl;
	cout<<"1 pInt2 引用计数:"<<pInt2.use_count()<<endl;

	pInt3 = pInt2;
	cout<<"2 pInt3 引用计数:"<<pInt3.use_count()<<endl;
	cout<<"2 pInt2 引用计数:"<<pInt2.use_count()<<endl;

	//get 和 reset,get不会改变引用计数
	Example * tmp = pInt3.get();
	cout<<"get pInt3 引用计数:"<<pInt3.use_count()<<endl;
	cout<<"get:"<<tmp->e<<endl;
	pInt3.reset(new Example(100));//首先生成新对象，然后引用计数减1，引用计数为0，故析构,最后将新对象的指针交给智能指针
	cout<<"3 pInt3 引用计数:"<<pInt3.use_count()<<endl;

	//weak_ptr指针的使用,weak_ptr没有-> 和 *，每次都需要赋值个一个shared_ptr tmp来操作。
	weak_ptr<Example>pInt4(pInt3);
	cout<<"weak_ptr 不改变 shared_ptr 的引用计数:"<<pInt3.use_count()<<endl;
	pInt3.reset();
	if(shared_ptr<Example> tmp = pInt4.lock()){
		cout<<"weak_ptr 不为空"<<tmp->e<<" pInt3 引用计数变为:"<<pInt3.use_count()<<endl;
	}
	else{
		cout<<"weak_ptr 为空"<<endl;
		cout<<pInt4.expired()<<endl;
	}
}	