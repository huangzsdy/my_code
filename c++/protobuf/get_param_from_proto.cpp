#include "caffe.pb.h"
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/text_format.h>

#include <iostream>
#include <fcntl.h>
#include <unistd.h>	

using namespace std;

using google::protobuf::io::FileInputStream;
using google::protobuf::io::FileOutputStream;
using google::protobuf::io::ZeroCopyInputStream;
using google::protobuf::io::ZeroCopyOutputStream;
using google::protobuf::io::CodedInputStream;
using google::protobuf::io::CodedOutputStream;
using google::protobuf::Message;

int main(){
	const char * filename = "solver.prototxt";
	caffe::SolverParameter solver_param;
	int fd = open(filename,O_RDONLY);
	if(fd == -1)
		cout<<"File not found"<<endl;
	FileInputStream * input = new FileInputStream(fd);
	bool success = google::protobuf::TextFormat::Parse(input,&solver_param);
	delete input;
	close(fd);
	cout<<"Solver Mode = "<<solver_param.solver_mode()<<endl;
	cout<<"test interval = "<<solver_param.test_interval()<<endl;
	cout<<"base lr = "<<solver_param.base_lr()<<endl;
	cout<<"net = "<<solver_param.net()<<endl;

}

