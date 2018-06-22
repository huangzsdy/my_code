#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(){
   //string  tmp = "a,b,c";
   string  tmp = "a";
   vector<char> v;
   char to_split = ',';
   string::size_type index;
   do{
     index = tmp.find_first_of(to_split);
     string sub = tmp.substr(0,index);
     tmp = tmp.substr(index + 1);
     cout<<sub<<endl;
     v.push_back(*sub.c_str());
   }while(index != string::npos);
   for(auto x:v)
       cout<<x<<" ";
}
