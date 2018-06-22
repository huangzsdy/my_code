#include <iostream>
#include <string>
#include <cstring>
#include <ext/hash_map>

using namespace std;
using namespace __gnu_cxx;//因为hash_map还未纳入std标准库,所以需要#include <ext/hash_map> 和 using namespace __gnu_cxx

struct compare_str1{
    bool operator()(const char*p1,const char * p2)const{
        return strcmp(p1,p2) == 0;
    }
};

struct compare_str2{
    const char * myStr;
    compare_str2(const char * str):myStr(str){};
    bool operator == (const char* anotherStr)const{
        return strcmp(myStr,anotherStr) == 0;
    }
};
/**
* const char *,string 表示key-value类型
* hash<const char*> 表示散列函数
* compare_str1 表示比较函数
**/
typedef hash_map <const char*,string,hash<const char*>,compare_str1> StrInMap;
StrInMap namemap;


int main(int argc,char ** argv){
    namemap["岳不群"] = "华山派掌门";
    namemap["张三丰"] = "太极拳法";
    namemap.insert(pair<const char*,string>("东方不败","葵花宝典"));
    pair<StrInMap::iterator,bool> pr = namemap.insert(pair<const char*,string>("张三丰2","太极拳"));//只能插入一个
    if(pr.second == true)
    {
        cout<< "The element was inserted successfully."<< endl;
    }
    else
    {
        cout<< "The element  already exists  with a key value of \n"
            << "((pr.first) -> first)= "<<(pr.first)-> first <<" ((pr.first)-> second) = "<<(pr.first->second)
            << "."<< endl;
    }
    StrInMap::iterator iter = namemap.begin();
    for(;iter != namemap.end();++iter)
        cout<<iter->first<<" "<<iter->second<<endl;
    cout<<namemap.size()<<endl;
    cout<<namemap.count("张三丰")<<endl;//count统计是否存在，1表示存在，0表示不存在
    return 0;
}