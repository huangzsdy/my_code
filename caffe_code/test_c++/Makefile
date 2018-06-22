GFLAGS=-Wall -DUNIX -O2 --std=c++11 -fPIC

CAFFE_ROOT=/home/huangzesang/share/caffe-master
ENV_ROOT=/home/software/local

blob:blob_demo.cpp
	g++ -o blob_demo blob_demo.cpp -I $(CAFFE_ROOT)/include -D CPU_ONLY -I $(ENV_ROOT)/include -I $(CAFFE_ROOT)/.build_release/src -L $(ENV_ROOT)/lib -lglog -lgflags -lboost_system -L $(CAFFE_ROOT)/build/lib -lcaffe

clean:
	rm -rf blob_demo
