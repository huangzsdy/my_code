#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;


void do_print_id(int id){
	std::unique_lock <std::mutex>lock(mtx);
	while(!ready)
	{
		cv.wait(lock);
		// std::cout<<id<<" ready :"<<ready<<std::endl;
		// continue;
	}
	std::cout<<"Thread "<<id<<std::endl;
}

void go(){
	std::unique_lock<std::mutex> lock(mtx);
	ready = true;
	cv.notify_all();
}

int main(){
	std::thread threads[10];
	for(int i = 0;i < 10;i++){
		threads[i] = std::thread(do_print_id,i);//线程初始化后就已经开始启动了，在do_print_id里调用wait，所以该线程阻塞了
	}
	std::cout<<"10 Threads ready to go"<<std::endl;
	go();
	std::cout<<"h"<<std::endl;
	for(auto & th:threads)
		th.join();
	return 0;
}