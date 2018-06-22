#include <iostream>
#include <boost/python.hpp>

using namespace  boost::python;

struct Num{    
Num();    
float get() const;    
void set(float value);
};

BOOST_PYTHON_MODULE(a){
class_<Num>("Num")
    .add_property("rovalue", &Num::get)
    .add_property("value", &Num::get, &Num::set);
}


