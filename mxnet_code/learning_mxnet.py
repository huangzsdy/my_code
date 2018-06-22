#coding:utf-8
import sys
import mxnet as mx
import numpy as np
import pickle as pkl

# numpy 中的 axis=n 就是在第n维上进行操作例如np.sum(a,axis=1)，就是在a的第1维上进行sum操作，对于第axis=0，即第0维上的数据没有影响
# 具体到二维数组，等同于，axis=0，就是在行上操作;axis=1，就是在列上操作


def t1():
	c = np.arange(15).reshape(3,5)
	a = mx.nd.array(c,mx.gpu(3))
	# float32 is used in default
	a = mx.nd.array([1,2,3])
	# create an int32 array
	b = mx.nd.array([1,2,3], dtype=np.int32)
	# create a 16-bit float array
	c = mx.nd.array([1.2, 2.3], dtype=np.float16)
	# create a 2-dimensional array full of zeros with shape (2,3)
	a = mx.nd.zeros((2,3))
	# create a same shape array full of ones
	b = mx.nd.ones((2,3))
	# create a same shape array with all elements set to 7
	c = mx.nd.full((2,3), 7)

	# create a same shape whose initial content is random and （empty 是随机产生，不是为0，注意！！）
	# depends on the state of the memory
	d = mx.nd.empty((2,3))

	# full 和 ones的区别，full是 1 * 4 * 2,ones是2 * 4 * 1
	a = mx.nd.full((2,4,1),1)
	b = mx.nd.ones((2,4,1))
	# print 'a',a,'b',b

	# * 和 dot的区别 ,星号是逐个相乘，dot是点乘
	a = mx.nd.array([1] * 4)
	b = a * a
	c = mx.nd.dot(a,a)
	# print 'b: %s,n c: %s'%(b.asnumpy(),c.asnumpy())
	



def t2():
	# 得到某个维度的数据，有点像切片
	a = mx.nd.array(np.arange(6).reshape(3,2))
	d = mx.nd.slice_axis(a,axis=1,begin=1,end=2)
	print 'a:',a.asnumpy().tolist(),'d:',d.asnumpy().tolist()

def t3():
# 这个不太懂 a[c:c]代表啥意思！！！和numpy 的 a[c:c](即为空)不一样，numpy和普通的list是一样的。但是a[b:c] 和 numpy,list是一样的
	a = mx.nd.array(np.arange(6).reshape(3,2))
	a[1:1] = 9	#会把整个a[1]都变成[9:9]
	b = np.arange(6).reshape(3,2)
	print 'a[0:0]:',a[:].asnumpy(),'b[1:1]:',b[1:1]

def t4():
	a = mx.nd.ones((2,3))
	b = mx.nd.ones((2,3))*2
	c = mx.nd.concat(a,b) #默认是在dim=1，即第1维上操作，mx.nd.concat(a,b,dim=0)则会在第0维操作
	print 'a:',a.asnumpy().tolist(),'c:',c.asnumpy().tolist()

def t5():
	a = mx.nd.array(np.arange(6).reshape(6,1))
	b = a.broadcast_to((6,4))  #广播，同一纬度地复制扩充
	c = a.reshape((2,1,1,3))
	d = c.broadcast_to((2,2,2,3))
	print 'b:',b.asnumpy().tolist(),'d:',d.asnumpy().tolist()

def t6():
	# broadcast 在不同维度的两个数组执行时加法和乘法时，会自动执行broadcast，
	a = mx.nd.ones((3,2))
	b = mx.nd.ones((1,2))
	c = a + b
	print 'a:',a.asnumpy().tolist(),'\nb:',b.asnumpy().tolist(),'\nc:',c.asnumpy().tolist()

def t7():
	gpu_devices = [mx.gpu(0),mx.gpu(1)]
	a = mx.nd.ones((1,2), mx.cpu())
	b = mx.nd.zeros((1,2), gpu_devices[0])
	c = mx.nd.ones((1,2), gpu_devices[1])
	a.copyto(c)  # copy from CPU to GPU
	# d = b + c
	# print 'b:',b,
	print 'b.content:',b.context
	e = b.as_in_context(c.context) + c  # same to above
	# print 'e:',e

def t8():
	# load and save 两种方式
	a = mx.nd.ones((2, 3))
	# pack and then dump into disk
	data = pkl.dumps(a)
	pkl.dump(data, open('tmp.pickle', 'wb'))
	# load from disk and then unpack
	data = pkl.load(open('tmp.pickle', 'rb'))
	b = pkl.loads(data)
	b.asnumpy()
	a = mx.nd.ones((2,3))
	b = mx.nd.ones((5,6))
	mx.nd.save("temp.ndarray", [a,b])
	c = mx.nd.load("temp.ndarray")
	d = {'a':a, 'b':b}
	mx.nd.save("temp.ndarray", d)
	c = mx.nd.load("temp.ndarray")