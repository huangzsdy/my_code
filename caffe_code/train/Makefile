GFLAGS=-Wall -DUNIX -O2 --std=c++11 -fPIC
ROOT=/home/software/local
CAFFE_ROOT=/home/huangzesang/share/caffe-test/build

INCLUDES=-I$(ROOT)/include     \
         -I$(ROOT)/../cuda/7.0/include \
         -I$(CAFFE_ROOT)/../include \
         -I$(CAFFE_ROOT)/src

LIBS=-L$(ROOT)/lib                         \
         -lopencv_core                       \
         -lopencv_highgui                    \
         -lopencv_ml                         \
         -lopencv_features2d                 \
         -lopencv_legacy                     \
         -lopencv_imgproc		    \
         -lboost_system                     \
         -lglog                             

test:classification.cpp
	g++ $(GFLAGS) $(INCLUDES) -o test classification.cpp $(LIBS) -L${CAFFE_ROOT}/lib -lcaffe  
clean:
	rm test
