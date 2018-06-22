#include <boost/python.hpp>

const char *hello(){return "olleh";}
const char * bye(){return "eyb";}
BOOST_PYTHON_MODULE(hello_bye)
{
using namespace boost::python;
def("hello", hello);
def("bye",bye);
}
