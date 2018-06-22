#include <iostream>
#include <boost/thread.hpp>
#include <memory>

using namespace std;


class A{
public:
	A(int a):a_(a){};
	void print(int c){
		if(boost::this_thread::interruption_requested())
			cout<<"Interrupted!"<<endl;

		cout<<c<<" "<<a_<<endl;
	}
private:
	int a_;
};


int main(int argc,char ** argv){
	A a(1);
	shared_ptr<boost::thread>  c;
	c.reset(new boost::thread(&A::print,&a,2));
	cout<<1<<endl;
	c->interrupt();
	c->join();
	
	return 0;
}