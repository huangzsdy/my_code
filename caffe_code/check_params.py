#coding:utf-8

'''
各种caffe的接口调用

'''
import os
import numpy as np
import matplotlib.pyplot as plt

caffe_root = '/home/huangzesang/share/caffe-master'
import sys
sys.path.insert(0,caffe_root + '/python')
import caffe

deploy = '/home/huangzesang/share/caffe-master/examples/cifar10/cifar10_full.prototxt'
caffe_model = '/home/huangzesang/share/caffe-master/examples/cifar10/cifar10_full_iter_70000.caffemodel.h5' 

net = caffe.Net(deploy,caffe_model,caffe.TEST)
transformer = caffe.io.Transformer({'data': net.blobs['data'].data.shape})
# transformer.set_mean('data',np.load(mean_file).mean(1).mean(1))
transformer.set_transpose('data', (2,0,1))	
transformer.set_channel_swap('data', (2,1,0))
transformer.set_raw_scale('data', 255.0)

#查看各层的参数，前馈的数据
def show_params():
	global net
	#打印所有参数的大小和
	print [(k,v[0].data.shape) for k,v in net.params.items()]  

	#打印某层的 conv1 的w和b，只有卷积和全连接有参数
	w = net.params['conv1'][0].data
	b = net.params['conv1'][1].data
	print w.shape
	print b.shape

	#前馈后某层的特征
	net.forward()
	fea = net.blobs['ip1'].data
	print fea

# 一次多张图片过前馈
def forward_batch():
	global net,transformer
	folder = '/home/safe_data_dir/CIFAR_image/CIFAR10/png/test/'
	batch = []
	for img in os.listdir(folder)[:9]:
		im = caffe.io.load_image(folder + img)
		batch.append(transformer.preprocess('data',im))
	out = net.forward_all(data=np.array(batch))
	print out['prob'].shape		#打印出prob层的值,即最后一层的输出，即概率
	for prob in out['prob']:
		print prob

def input_output():
	global transformer
	folder = '/home/tmp_data_dir_2/huangzesang/BaiduBigData2017/train/'
	imgs =[folder + o for o in os.listdir(folder)]
	im = caffe.io.load_image(imgs[1])
	net.blobs['data'].data[...] = transformer.preprocess('data',im)

	plt.imshow(transformer.deprocess('data',net.blobs['data'].data[0]))
	plt.savefig('test.jpg')

# 读均值文件和把均值写到文件里
def convert_meanfile():
	#均值文件
	mean_file = '/home/huangzesang/share/caffe-master/examples/cifar10/mean.binaryproto'

	#将均值文件读入blob中
	mean_blob = caffe.proto.caffe_pb2.BlobProto()
	mean_blob.ParseFromString(open(mean_file,'rb').read())

	#将均值blob转为numpy数组,因为mean_npy是 1*3*h*w，所以取第一个作为均值
	mean_npy = caffe.io.blobproto_to_array(mean_blob)[0]

	print 'mean.shape',mean_npy.shape
# 创建mean.npy 和读取mean.npy
def create_mean():
	MEAN_NPY_PATH = 'mean.npy'
	mean = np.ones([3,256, 256], dtype=np.float)
	mean[0,:,:] = 104
	mean[1,:,:] = 117
	mean[2,:,:] = 123

	# np.save(MEAN_NPY_PATH, mean)
	mean_npy = np.load(MEAN_NPY_PATH)
	mean = mean_npy.mean(1).mean(1)
	print mean
	return mean

#除了forward以外，可以用classifier来初始化网络，其实从源码中可知，classifier继承自caffe.Net
def make_classifier():
	img_path = 'test.jpg'
	mean_npy = create_mean()
	classifier = caffe.Classifier(deploy,caffe_model,image_dims=(32,32),mean=mean_npy,channel_swap=(2,1,0),raw_scale=255)
	input_image = caffe.io.load_image(img_path)
	output = classifier.predict([input_image])
	print output[0]


#----------------------------------------
# 利用solver来获得网络
def use_solver():
	solver_file = '/home/huangzesang/share/caffe-master/examples/cifar10/cifar10_quick_solver.prototxt'
	solver = caffe.get_solver(solver_file)
	# solver.solve()	#这是开始进行训练，直到训练完成才停止
	# solver.step(1)	#这是进行一次迭代
	tmp = solver.test_nets[0].blobs
	for k,v in tmp.iteritems():
		print k,v
	print
	tmp = solver.test_nets[0].params
	for k,v in tmp.iteritems():
		print k,v
	solver.test_nets[0].forward() #测试集的一个iter过一次前馈
	acc = solver.test_nets[0].blobs['accuracy'].data
	print 'acc:',acc




# show_params()
forward_batch()
# input_output()
# convert_meanfile()
# create_mean()
# use_solver()
# make_classifier()
