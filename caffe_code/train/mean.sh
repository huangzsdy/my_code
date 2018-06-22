#!/bin/bash
TOOLS=/home/huangzesang/share/caffe-test/build/tools
PWD=`pwd`
$TOOLS/compute_image_mean.bin $PWD/cifar10_train_lmdb/  $PWD/mean.binaryproto
