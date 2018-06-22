set -x

LD_LIBRARY_PATH=/home/huangzesang/caffe/build/lib:$LD_LIBRARY_PATH
BASE=/home/huangzesang/caffe/examples/cifar10
IMAGE_LIST=test.list
IMAGE_FOLDER=/home/safe_data_dir/CIFAR_image/CIFAR10/png/test/

./test $BASE/cifar10_quick.prototxt \
       $BASE/cifar10_quick_iter_5000.caffemodel.h5 \
       $BASE/mean.binaryproto \
       $BASE/synset.txt \
       $IMAGE_FOLDER/../../$IMAGE_LIST \
       $IMAGE_FOLDER 
