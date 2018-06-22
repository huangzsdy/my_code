//#include <boost/algorithm/string.hpp>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int main(int argc,char **argv){
    string tmp = "a/b/c";
    string t2 = tmp.substr(tmp.find_last_of("/")+1);
    cout<<"t2 is"<<t2<<endl;
    /*
    vector<string> fields;
    split(fields,tmp,boost::is_any_of("/"));
    for(vector<string>::iterator iter = fields.begin();iter != fields.end();iter++){
        cout<<*iter<<endl;
    }*/
}
