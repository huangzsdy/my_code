clude <iostream>
#include <cstring>
#include <string>
#include <vector>
#include "zookeeper.h"
#include "zookeeper_log.h"

using namespace std;

/***********************
watcher: 触发函数，当节点状态改变会触发
ZkUtils: 封装一些常用的方法
************************/


void watcher(zhandle_t * zh,int type, int state ,const char* path,void * watcherCtx){
//	cout<<"Something happened , trigger this function"<<endl;
//	cout<<"type:"<<type<<" "<<"state:"<<state<<" "<<"path:"<<path<<" "<<watcherCtx<<endl;
}

class ZkUtils{
	public :
		ZkUtils(string Host,int Timeout);
		~ZkUtils();

		int create(string path,string value);
		string get(string path);
		int set(string path,string value);
		bool exists(string path);
		vector<string> getChildren(string path);

	private:
		string host;
		int timeOut;
		zhandle_t * zkHandle;
};

ZkUtils::ZkUtils(string Host,int Timeout){
	host = Host;
	timeOut = Timeout;
	zkHandle = zookeeper_init(host.c_str(),watcher,timeOut,0,0,0);
	if(zkHandle == NULL){
		throw string("zkHandle init fail!");
	}
}

ZkUtils::~ZkUtils(){
	int flag = zookeeper_close(zkHandle);
	if (flag == ZOK)
		cout<<"disconnect zookeeper connection success"<<endl;
}

int ZkUtils::create(string path,string value){
	char path_buffer[64];
	int buffer_length = sizeof(path_buffer);
	
	int flag = zoo_create(zkHandle,path.c_str(),value.c_str(),value.size(),&ZOO_OPEN_ACL_UNSAFE,0,path_buffer,buffer_length);
	cout<<"path:"<<path<<" "<<"value:"<<value<<" flag:"<<flag<<endl;

	if(flag!=ZOK){
		cout<<"failed to create node"<<endl;
		return -1;
	}
	else{
		cout<<"create node:"<<path_buffer<<" success!"<<endl;
		return 0;
	}
}

string ZkUtils::get(string path){
	char buffer[1024];
	int bufferLength = sizeof(buffer);
	int flag = zoo_get(zkHandle,path.c_str(),0,buffer,&bufferLength,NULL);
	if (flag == ZOK){
		string value = string(buffer,bufferLength);
		return  value;
	}
	else
		return NULL;
}

int ZkUtils::set(string path,string value){
	int flag = zoo_set(zkHandle,path.c_str(),value.c_str(),value.size(),0);
	if (flag != ZOK){
		cout<<"set node:"<<path<<" data:"<<value<<"failed"<<endl;
		return -1;
	}
	else{
		cout<<"set node:"<<path<<" success"<<endl;
		return 0;
	}
}

bool ZkUtils::exists(string path){
	struct Stat stat;
	int flag = zoo_exists(zkHandle,path.c_str(),1,&stat);
	if(flag == ZOK){
		cout<<"node exists:"<<path<<endl;
		return true;
	}
	else{
		cout<<"node do not exist:"<<path<<endl;
		return false;
	}
}

vector<string> ZkUtils::getChildren(string path){
	struct String_vector strings;
	vector<string> childs;
	int flag = zoo_get_children(zkHandle,path.c_str(),0,&strings);
	if(flag == ZOK){
		for(int32_t i = 0;i < strings.count;++i){
			cout<<strings.data[i]<<" ";
			childs.push_back(string(strings.data[i]));
		}
		cout<<endl;
	}
	else{
		cout<<"get Children failed,flag is:"<<flag<<endl;
	}
	return childs;
}


int main(int argc,char ** argv){
	string host = "localhost:2181"; //zookeeper的IP
	int timeout = 30000;
	string path = "/hello";
	string value = "for test";

	zoo_set_debug_level(ZOO_LOG_LEVEL_WARN);
	ZkUtils zk_test = ZkUtils(host,timeout);
	//vector<string> childs = zk_test.getChildren(path);
	//for (int i = 0;i < childs.size();++i)
	//	cout<<childs[i]<<" ";
	int status = zk_test.create(path,value);
	string result = zk_test.get(path);
	cout<<"data of "<<path<<" is:"<<result<<endl;
	bool exists = zk_test.exists(path);
	status = zk_test.set(path,"fdfd");
	string result1 = zk_test.get(path);
	cout<<"修改后，"<<result1<<endl;
	return 0;
}

