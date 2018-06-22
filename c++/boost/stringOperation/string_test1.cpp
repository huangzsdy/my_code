#include <iostream>
#include <locale>
#include <clocale>
#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <boost/format.hpp>

int main(int argc,char ** argv){
   std::setlocale(LC_ALL,"German");
   std::string s = "Bo Daf";
   std::cout<<boost::algorithm::to_upper_copy(s)<<std::endl;//返回一个全大写的对象
   std::cout<<boost::algorithm::to_lower_copy(s)<<std::endl;//返回一个全大写的对象
   boost::algorithm::to_upper(s);//把s改成全大写
   std::cout<<s<<std::endl; 

  s = "Boris Schäling"; 

  std::cout << boost::algorithm::erase_first_copy(s, "i") << std::endl; 
  std::cout << boost::algorithm::erase_nth_copy(s, "i", 1) << std::endl; 
  std::cout << boost::algorithm::erase_last_copy(s, "i") << std::endl; 
  std::cout << boost::algorithm::erase_all_copy(s, "i") << std::endl; 
  std::cout << boost::algorithm::erase_head_copy(s, 5) << std::endl; 
  std::cout << boost::algorithm::erase_tail_copy(s, 8) << std::endl;

  boost::iterator_range<std::string::iterator> r = boost::algorithm::find_first(s, "Boris"); 
  std::cout << r << std::endl; 
  r = boost::algorithm::find_first(s, "xyz"); 
  std::cout << r << std::endl;

//是否包含
  std::cout << boost::algorithm::contains(s, "fdis") << std::endl;

 
//字符串拼接 join , split
  std::cout<<"字符串拼凑"<<std::endl;
  std::vector<std::string> v; 
  v.push_back("Boris"); 
  v.push_back("Schäling"); 
  std::cout << boost::algorithm::join(v, "_") << std::endl;
  v.clear();

  boost::algorithm::split(v, s, boost::is_any_of(" ")); 
  std::cout << v.size() << std::endl; 


//正则匹配
  std::cout<<"正则匹配"<<std::endl;
  s = "Boris Schäling"; 
  boost::regex expr("(\\w+)\\s(\\w+)"); 
  boost::smatch what; 
  if (boost::regex_search(s, what, expr)) 
  { 
    std::cout << typeid(what[0]).name()<<what[0] << std::endl; 
    std::cout << typeid(what[1]).name()<<what[1] << " " << what[2] << std::endl; 
  } 

//字符串格式化输出
  std::cout << boost::format("#%s %d %04d") % s % 100 % 99 << std::endl;
  return 0;
}
