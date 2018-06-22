#!/usr/bin/en sh
set -x
BUILD=/home/huangzesang/share/caffe-master
DATA=/home/safe_data_dir/CIFAR_image/CIFAR10
STORE=/home/huangzesang/share/caffe-test/examples/cifar10

rm -rf $STORE/cifar10_train_lmdb
$BUILD/build/tools/convert_imageset --shuffle \
               $DATA/png/train/ \
               $DATA/train.list  $STORE/cifar10_train_lmdb

rm -rf $STORE/cifar10_test_lmdb
$BUILD/build/tools/convert_imageset --shuffle \
               $DATA/png/test/ \
               $DATA/test.list  $STORE/cifar10_test_lmdb

        #--resize_height=136 --resize_width=136 \
