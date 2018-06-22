"""Generation script for residual networks."""
import numpy as np

__author__      = "Marcel Simon"
__copyright__   = "BSD 2-clause"

import sys
sys.path.insert(0,"/home/huangzesang/share/caffe-master/python")
import caffe
from caffe import layers as L, params as P, to_proto

def group_conv_1x1(bottom, nout, group):
    conv = L.Convolution(bottom, kernel_size=1, stride=1,
            num_output=nout, pad=0, group=group, bias_term=False, param = [dict(lr_mult=1, decay_mult=1)],
            weight_filler=dict(type="msra"))
    bn = L.BatchNorm(conv, param=[dict(lr_mult=0),dict(lr_mult=0),dict(lr_mult=0)], in_place=True)
    scale = L.Scale(bn,scale_param=dict(bias_term=True), param=[dict(lr_mult=1, decay_mult=1),dict(lr_mult=2, decay_mult=1)],in_place=True)
    return conv, bn, scale

def dw_conv_3x3(bottom, nout, stride = 1):
    conv = L.ConvolutionDepthwise(bottom, kernel_size=3, stride=stride,
            num_output=nout, pad=1, bias_term=False, param = [dict(lr_mult=1, decay_mult=1)],
            weight_filler=dict(type="msra"))

    bn = L.BatchNorm(conv, param=[dict(lr_mult=0),dict(lr_mult=0),dict(lr_mult=0)], in_place=True)
    scale = L.Scale(bn,scale_param=dict(bias_term=True), param=[dict(lr_mult=1, decay_mult=1),dict(lr_mult=2, decay_mult=1)],in_place=True)
    return conv, bn, scale

def se_unit(bottom, nout):
    global_pool = L.Pooling(bottom, pooling_param = dict(pool = 1, global_pooling = True))
    fc1 = L.InnerProduct(global_pool, num_output = nout/16,
              param=[dict(lr_mult=1, decay_mult=1)],
              weight_filler=dict(type="msra"))
    relu = L.ReLU(fc1, in_place=True)
    fc2 = L.InnerProduct(relu, num_output = nout,
              param=[dict(lr_mult=1, decay_mult=1)],
              weight_filler=dict(type="msra"))
    sigmoid = L.Sigmoid(fc2)
    scale = L.Scale(bottom, sigmoid, axis=0)
    return global_pool, fc1, relu, fc2, sigmoid, scale

def standard_unit(n, nout, s, group, se = False, newdepth = False, is_first=False):
    """
    This creates the "standard unit" shown on the left side of Figure 5.
    """
    net = n.__dict__['tops']

    bottom = net[list(net.keys())[-1]] #find the last layer in netspec
    stride = 2 if newdepth else 1

    if is_first:
        net[s + 'conv1'], net[s + 'bn1'], net[s + 'scale1'] = group_conv_1x1(bottom, nout = nout, group=1)
        net[s + 'relu1'] = L.ReLU(net[s + 'scale1'], in_place=True)
        net[s + 'conv2'], net[s + 'bn2'], net[s + 'scale2'] = dw_conv_3x3(net[s + 'relu1'], stride = stride, nout = nout)
    else:
        net[s + 'conv1'], net[s + 'bn1'], net[s + 'scale1'] = group_conv_1x1(bottom, nout = nout, group=group)
        net[s + 'relu1'] = L.ReLU(net[s + 'scale1'], in_place=True)
        net[s + 'shuffle'] = L.ShuffleChannel(net[s + 'relu1'], group = group)
        net[s + 'conv2'], net[s + 'bn2'], net[s + 'scale2'] = dw_conv_3x3(net[s + 'shuffle'], stride = stride, nout = nout)

    net[s + 'conv3'], net[s + 'bn3'], net[s + 'scale3']  = group_conv_1x1(net[s + 'scale2'], nout = 4*nout, group=group)

    if newdepth:
        if se:
            net[s + 'se_global_pool'], net[s + 'se_fc1'], net[s + 'se_relu'], net[s + 'se_fc2'], net[s + 'se_sigmoid'], net[s + 'se_scale'] = se_unit(net[s + 'scale3'], nout*4)
            net[s + 'pool'] = L.Pooling(bottom, stride = 2, kernel_size = 3, pooling_param = dict(pool = 1))
            net[s + 'concat'] = L.Concat(net[s + 'se_scale'], net[s + 'pool'])
        else:
            net[s + 'pool'] = L.Pooling(bottom, stride = 2, kernel_size = 3, pooling_param = dict(pool = 1))
            net[s + 'concat'] = L.Concat(net[s + 'scale3'], net[s + 'pool'])
        net[s + "relu_final"] = L.ReLU(net[s + 'concat'], in_place=True)
    else:
        if se:
            net[s + 'se_global_pool'], net[s + 'se_fc1'], net[s + 'se_relu'], net[s + 'se_fc2'], net[s + 'se_sigmoid'], net[s + 'se_scale'] = se_unit(net[s + 'scale3'], nout*4)
            net[s + 'sum'] = L.Eltwise(net[s + 'se_scale'], bottom)
        else:
            net[s + 'sum'] = L.Eltwise(net[s + 'scale3'], bottom)
        net[s + "relu_final"] = L.ReLU(net[s + 'sum'], in_place=True)

def shuffle_net(group, scale_f, input_size, se = False,num_classes = 1000, asoft=True):
    # figure out network structure
    group_defs = {
        1: [36, 72, 144],
        2: [50, 100, 200],
        3: [60, 120, 240],
        4: [68, 136, 272],
        8: [96, 192, 384],
    }
    nouts_list = [int(v * scale_f)for v in group_defs[group]]
    nunits_list = [3, 7, 3]
    f_size = 24

    # setup the first couple of layers
    n = caffe.NetSpec()
    net = n.__dict__['tops']

    n.data, n.label = L.ImageData(batch_size=128,
                source="../data/train.list",
                root_folder="/",ntop=2,
                include=dict(phase=0),
                transform_param=dict(crop_size=input_size, mirror=True, scale= 1/128.))

    # The data mean
    n.conv1 = L.Convolution(n.data, kernel_size=3, stride=2,
            num_output=f_size, pad=1, bias_term=False, param = [dict(lr_mult=1, decay_mult=1)],
            weight_filler=dict(type="msra"))
    n.conv1_bn = L.BatchNorm(n.conv1, param=[dict(lr_mult=0),dict(lr_mult=0),dict(lr_mult=0)], in_place=False)
    n.conv1_scale = L.Scale(n.conv1_bn,scale_param=dict(bias_term=True), param=[dict(lr_mult=1, decay_mult=1),dict(lr_mult=2, decay_mult=1)],in_place=True)
    n.conv1_relu = L.ReLU(n.conv1_scale, in_place=True)
    n.conv1_pool = L.Pooling(n.conv1_relu, stride = 2, kernel_size = 3)
    # make the convolutional body

    last_size = f_size/4
    for i, (nout, nunit) in enumerate(zip(nouts_list, nunits_list)):
        s = 'Step' + str(i+1) + '_reduction_'
        if i == 0:
            standard_unit(n, nout - last_size, s, group, se = se, newdepth=True, is_first=True)
        else:
            standard_unit(n, nout - last_size, s, group, se = se, newdepth=True)
        last_size = nout
        for unit in range(nunit):
            s = 'Step' + str(i+1) + '_'+str(unit+1)+'_'
            standard_unit(n, nout, s, group, se = se)

    # add the end layers

    net = n.__dict__['tops']
    bottom = net[list(net.keys())[-1]] #find the last layer in netspec

    n.global_pool = L.Pooling(bottom, pooling_param = dict(pool = 1, global_pooling = True))
    n.score = L.InnerProduct(n.global_pool, num_output = num_classes, bias_term=False,
                         param=[dict(lr_mult=1, decay_mult=1)],
                        weight_filler=dict(type="msra"))
    n.loss = L.SoftmaxWithLoss(n.score, n.label)
    n.accuracy = L.Accuracy(n.score, n.label)

    return n

def train(g,s1,se):
    s = ''
    s += "nohup \\\n"
    s += "../caffe-master/build/tools/caffe train \\\n"
    s += "--solver=./solver/g{}_s{}{}.solver \\\n".format(g,s1,se)
    s += "--gpu=$1 \\\n"
    s += ">> logs/log.g{}_s{}{} &\n".format(g,s1,se)
    return s
def solver(g,s1,se):
    s = ''
    s += "base_lr: {}\n".format(0.05/np.sqrt(g))
    s += "lr_policy: \"poly\"\n"
    s += "power:1\n"
    #s += "stepvalue:180000\n"
    #s += "stepvalue:270000\n"

    s += "momentum: 0.9\n"
    s += "weight_decay: 0.00004\n"

    s += "display: 50\n"
    s += "max_iter: 300000\n"
    s += "snapshot: 10000\n"
    s += "snapshot_prefix: \"models/g{}_s{}{}\"\n".format(g, s1, se)
    s += "net: \"prototxt/g{}_s{}{}.prototxt\"\n".format(g, s1, se)
    s += "test_initialization: true\n"
    s += "test_iter: 200\n"
    s += "test_interval: 5000\n"
    return s

if __name__=='__main__':

    g = int(sys.argv[1])
    s = int(sys.argv[2])
    if len(sys.argv)==4:
        se = sys.argv[3]
    else:
        se = ""
    model_path = "prototxt/g{}_s{}{}.prototxt".format(g, s, se)
    solver_path = "solver/g{}_s{}{}.solver".format(g, s, se)
    train_path = "scripts/g{}_s{}{}.sh".format(g, s, se)

    model_info = shuffle_net(g, s, 128, se, num_classes = 17452, asoft=False).to_proto()
    solver_info = solver(g,s,se)
    train_info = train(g,s,se)
    with open(model_path,'w')as fp:
        print >>fp, model_info
    with open(solver_path,'w')as fp:
        fp.write(solver_info)
    with open(train_path,'w')as fp:
        fp.write(train_info)


