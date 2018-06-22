#include <boost/thread.hpp> 
#include <iostream> 

void wait(int seconds) 
{ 
  boost::this_thread::sleep(boost::posix_time::seconds(seconds)); 
} 

void thread(const char * tmp,int a) 
{ 
  for (int i = 0; i < 5; ++i) 
  { 
//    wait(1); 
    std::cout << tmp<<" : "<<i << std::endl; 
  } 
} 

int main() 
{ 
  boost::thread t1(thread,"1",1); 
  boost::thread t2(thread,"2",2); 
  t1.join(); 
  t2.join(); 
}
