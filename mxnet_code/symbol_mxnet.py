#coding:utf-8
import sys

mxnet_path = '/home/huangzesang/share/mxnet'
sys.path.insert(0,mxnet_path + '/python')

import mxnet as mx

def plot1():
    # lhs = mx.symbol.Variable('data1')
    # rhs = mx.symbol.Variable('data2')
    # net = mx.symbol.FullyConnected(data=lhs + rhs, name='fc1', num_hidden=128)   
    # print 'net arguments:',net.list_arguments()

    data = mx.symbol.Variable('data')
    net1 = mx.symbol.FullyConnected(data=data, name='fc1', num_hidden=10)
    net2 = mx.symbol.Variable('data2')
    net2 = mx.symbol.FullyConnected(data=net2, name='fc2', num_hidden=10)
    composed = net2(data2=net1, name='composed')
    print 'composed list_arguments:',composed.list_arguments()
    a = mx.viz.plot_network(symbol=composed,save_format='jpg',title='test-symbol',hide_weights=False,node_attrs={"shape":'rect',"fixedsize":'false'})

def plot2():
    data = mx.sym.Variable(name="data")
    net = data
    n_layer = 2
    for i in range(n_layer):
        with mx.name.Prefix("layer%d_" % (i + 1)):
            net = mx.sym.FullyConnected(data=net, name="fc", num_hidden=100)

    shape = {"data":(128,3,29,29)}
    a = mx.viz.plot_network(symbol=net,save_format='jpg',shape=shape,node_attrs={"shape":'rect',"fixedsize":'false'})
    a.render()

def plot3():
    def ConvFactory(data, num_filter, kernel, stride=(1,1), pad=(0, 0),name=None, suffix=''):
        conv = mx.sym.Convolution(data=data, num_filter=num_filter, kernel=kernel,
                      stride=stride, pad=pad, name='conv_%s%s' %(name, suffix))
        bn = mx.sym.BatchNorm(data=conv, name='bn_%s%s' %(name, suffix))
        act = mx.sym.Activation(data=bn, act_type='relu', name='relu_%s%s'
                      %(name, suffix))
        return act
    input = mx.sym.Variable(name="input")
    conv_comp = ConvFactory(data=input, num_filter=64, kernel=(7,7), stride=(2, 2))
    # shape = {"Previous Output" : (128, 3, 28, 28)}
    # a = mx.viz.plot_network(symbol=conv_comp,shape=shape,save_format='jpg')
    # a.render()

    ex = input.bind(ctx=mx.cpu(), args={'a':mx.nd.ones((2,3)),'b':mx.nd.ones((1,5)),'input':mx.nd.ones((1,5))})
    ex.forward()
    print('number of outputs = %d\nthe first output = \n%s' % (
           len(ex.outputs), ex.outputs[0].asnumpy()))

def t1():
    a = mx.sym.Variable('a')
    b = mx.sym.Variable('b')
    b = a + a * a

    data = mx.nd.ones((2,3))*2
    ex = b.bind(ctx=mx.cpu(), args={'a':data, 'b':data})
    ex.forward()
    print '2',ex.outputs[0].asnumpy()

if __name__ == '__main__':
    plot3()