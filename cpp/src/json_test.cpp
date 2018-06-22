#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

using namespace std;
using namespace boost::property_tree;

int main(int argc,char **argv){
	ptree pt_1,pt_11,pt_12;
	pt_11.put("id","abc");
	pt_11.put<int>("age",29);
	pt_11.put("name","chen");

	pt_12.push_back(make_pair("",pt_11));
	pt_1.put_child("data",pt_12);
	// ostringstream os;
	ofstream os;
	os.open("tmp.txt");
	write_json(os,pt_1);
	// cout<<os.str()<<endl;
	os.close();
	return 0;
}