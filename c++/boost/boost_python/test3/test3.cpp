#include <Python.h>
#include <iostream>
#include <boost/python.hpp>
#include <string>

using namespace  boost::python;
using namespace std;

class World{
public:
	World(string msg):msg(msg){}
	World(double a, double b){}
	void set(string msg){this->msg = msg;}
	string greet(){return msg;}
	string msg;
};


struct Foo {
	Foo(int x):x(x){}
	int get_x(){return x;}
	int x;
};
Foo * make_foo(int x){return new Foo(x);}
BOOST_PYTHON_MODULE(test3){
	def("make_foo",make_foo,return_value_policy<manage_new_object>());
	class_<World>("World",init<string>())
		.def(init<double,double>())
		.def("greet",&World::greet)
		.def("set",&World::set);

	class_<Foo>("Foo")
		.def("get_x",&Foo::get_x);
}


