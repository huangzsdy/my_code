#include <boost/thread/thread.hpp>  
#include <boost/thread/mutex.hpp>  
#include <iostream>  
  
boost::mutex io_mutex;  
// 可以用对象来创建线程，只要这个对象有重载 operator(){}的方法，class也类似  
// mutex.lock() 可以获得线程锁,即会等到本线程执行完，才会执行下一个线程
// boost::lock_guard<boost::mutex> lock(mutex) 这个类内部构造和析构函数会分别调用lock和unlock，所以可以用它代替mutex.lock和mutex.unlock,但是只能等到本线程执行完才能释放锁，分别写lock和unlock会更灵活一些
struct count  
{  
    count(int id) : id(id) {}  
  
    void operator()()  
    {  
        //boost::lock_guard<boost::mutex> lock(io_mutex);
        std::cout << "Thread " << boost::this_thread::get_id() << ": " << id << std::endl;
        io_mutex.lock();
        for(int i = 0; i < 10; ++i)  
        {  
            std::cout<<id<<": "<<i<<std::endl;  
        }  
        io_mutex.unlock();
    }  
  
    int id;  
};  
  
int main()  
{  
    
    boost::thread thrd1(count(1));  
    boost::thread thrd2(count(2));  
    thrd1.join();  
    thrd2.join();  
  
    return 0;  
} 
