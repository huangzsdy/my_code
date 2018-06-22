# -*- coding: utf-8 -*-
caffe_root = '/home/huangzesang/caffe-ssd/'
import sys
sys.path.insert(0,caffe_root + 'python')

from caffe.proto import caffe_pb2
s = caffe_pb2.SolverParameter()

path='./'
solver_file=path+'solver1.prototxt'

s.train_net = path+'train.prototxt'
s.test_net.append(path+'val.prototxt')
s.test_interval = 782  
s.test_iter.append(313) 
s.max_iter = 78200 

s.base_lr = 0.001 
s.momentum = 0.9
s.weight_decay = 5e-4
s.lr_policy = 'step'
s.stepsize=26067
s.gamma = 0.1
s.display = 782
s.snapshot = 7820
s.snapshot_prefix = 'shapshot'
s.type = "SGD"
s.solver_mode = caffe_pb2.SolverParameter.GPU

with open(solver_file, 'w') as f:
    f.write(str(s))
