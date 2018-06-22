#include <iostream>
#include <vector>
#include <caffe/blob.hpp>
#include <caffe/util/io.hpp>

using namespace caffe;
using namespace std;

int main(int argc,char ** argv){
	Blob<float> a;
	cout<<"Size : "<<a.shape_string()<<endl;
	a.Reshape(1,2,3,4);
	cout<<"Size : "<<a.shape_string()<<endl;
	
	//用mutable_cpu[gpu]_data[diff]	来修改内部数值.
	float * p = a.mutable_cpu_data();
	float * q = a.mutable_cpu_diff();
	//初始化为 0,1,2,3...
	for(int i = 0 ;i < a.count();++i){
		p[i] = i;
		q[i] = a.count() - i - 1;
	}
	//执行update，将data和diff融合,进行了 data = data - diff
	a.Update();

	for(int u = 0;u < a.num();++u){
		for(int v = 0;v < a.channels();++v){
			for(int w = 0;w < a.height();++w){
				for(int x = 0;x < a.width();++x){
					cout<<"a["<<u<<"]["<<v<<"]["<<w<<"]["<<x<<"] = "<<a.data_at(u,v,w,x)<<endl;
				}
			}
		}
	}
	cout<<"-----------"<<endl;
	//Blob 保存到磁盘，从磁盘载入内存。
	BlobProto bp; // 构造一个BlobProto对象
	a.ToProto(&bp,true);//将 a 序列化，连同diff(默认不带)
	WriteProtoToBinaryFile(bp,"a.blob");//
	BlobProto bp2;//
	ReadProtoFromBinaryFileOrDie("a.blob",&bp2);//从磁盘读取
	Blob<float> b;//
	b.FromProto(bp2,true);//从序列化对象bp2中克隆b(连同形状)

	for(int u = 0;u < b.num();++u){
		for(int v = 0;v < b.channels();++v){
			for(int w = 0;w < b.height();++w){
				for(int x = 0;x < b.width();++x){
					cout<<"b["<<u<<"]["<<v<<"]["<<w<<"]["<<x<<"] = "<<b.data_at(u,v,w,x)<<endl;
				}
			}
		}
	}

	cout<<"ASUM = "<<b.asum_data()<<endl;//L1 范数
	cout<<"SUMSQ = "<<b.sumsq_data()<<endl;//L2 范数
}