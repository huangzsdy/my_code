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

test_folder = '/home/safe_data_dir_2/huangzesang/dataset/CIFAR10/png/test/'
image_folder = '/home/safe_data_dir_2/huangzesang/dataset/CIFAR10'

deploy = '/home/huangzesang/share/learning/my_code/caffe_code/caffe-test/examples/cifar10/test/dropout/cifar10_quick.prototxt'
caffe_model = '/home/huangzesang/share/learning/my_code/caffe_code/caffe-test/examples/cifar10/test/dropout/models/cifar10_quick_iter_10000.caffemodel'
mean_file = '/home/huangzesang/share/learning/my_code/caffe_code/caffe-test/examples/cifar10/mean.npy'

caffe.set_mode_gpu()
net = caffe.Net(deploy,caffe_model,caffe.TEST)
transformer = caffe.io.Transformer({'data': net.blobs['data'].data.shape})
transformer.set_transpose('data', (2,0,1))
transformer.set_mean('data',np.load(mean_file).mean(1).mean(1))
# transformer.set_mean('data',np.array([113.865,122.95,125.307]))
transformer.set_raw_scale('data', 255.0)    
# transformer.set_channel_swap('data', (2,1,0))


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
def forward_batch(imgs):
    batch = []
    for img in imgs:
        im = caffe.io.load_image(img)
        batch.append(transformer.preprocess('data',im))
    out = net.forward_all(data=np.array(batch))
    # print out['prob'].shape       #打印出prob层的值,即最后一层的输出，即概率

    # for prob in out['prob']:
        # print prob
    # print out['prob']
    return out['prob']

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

#打印传入的data,特征图
def vis_square(data,fileName):
    """Take an array of shape (n, height, width) or (n, height, width, 3)
       and visualize each (height, width) thing in a grid of size approx. sqrt(n) by sqrt(n)"""
    
    # normalize data for display
    data = (data - data.min()) / (data.max() - data.min())
    
    # force the number of filters to be square
    n = int(np.ceil(np.sqrt(data.shape[0])))
    padding = (((0, n ** 2 - data.shape[0]),
               (0, 1), (0, 1))                 # add some space between filters
               + ((0, 0),) * (data.ndim - 3))  # don't pad the last dimension (if there is one)
    data = np.pad(data, padding, mode='constant', constant_values=1)  # pad with ones (white)
    
    # tile the filters into an image
    data = data.reshape((n, n) + data.shape[1:]).transpose((0, 2, 1, 3) + tuple(range(4, data.ndim + 1)))
    data = data.reshape((n * data.shape[1], n * data.shape[3]) + data.shape[4:])
    plt.savefig(fileName)
    # plt.imshow(data)
    # plt.axis('off')


#----------------------------------------
# 利用solver来获得网络
def use_solver():
    solver_file = '/home/huangzesang/share/caffe-master/examples/cifar10/cifar10_quick_solver.prototxt'
    solver = caffe.get_solver(solver_file)
    # solver.solve()    #这是开始进行训练，直到训练完成才停止
    # solver.step(1)    #这是进行一次迭代
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


def test1():
    global test_folder
    with open(image_folder + '/test.list','r') as f:
        test_list = f.read().splitlines()

    groudtruth = [int(_.split()[-1]) for _ in test_list]
    test_list = [os.path.join(test_folder,o.split()[0]) for o in test_list]

    predict_result = []

    batch_size = 10
    left_ = len(test_list)%batch_size
    round_ = len(test_list)/batch_size
    i = 0
    while i < round_ + 1:
        imgs = test_list[i * batch_size:(i + 1) * batch_size]
        batch_result = forward_batch(imgs)
        if len(imgs) > 0:
            labels_result = batch_result.argsort()[:,-1]
            predict_result += labels_result.tolist()
        i += 1

    count = 0
    for i in xrange(len(predict_result)):
        # print  predict_result[i],groudtruth[i],type(predict_result[i]),type(groudtruth[i])
        if predict_result[i] == groudtruth[i]:
            count += 1
        print 'test done.accuray:%.4f'%(1.0 * count / (i+1))

def test2():
    global test_folder,net
    net.blobs['data'].reshape(1,3,32,32)
    
    with open(image_folder + '/test.list','r') as f:
        test_list = f.read().splitlines()

    groudtruth = [int(_.split()[-1]) for _ in test_list]
    test_list = [os.path.join(test_folder,o.split()[0]) for o in test_list]

    count = 0
    predict_result = []
    for i in xrange(len(test_list)):
        image = caffe.io.load_image(test_list[i])
        transformed_image = transformer.preprocess('data',image)
        net.blobs['data'].data[...] = transformed_image 
        net.forward()
        output_prob = net.blobs['prob'].data[0]
        predict_label = output_prob.argmax()

        if groudtruth[i] == predict_label:
            count += 1
        print 'test done.accuray:%.4f'%(1.0 * count / (i+1))

def test3():
    def load_model():
        mean = np.array([113.865,122.95,125.307]*32*32).reshape(3,32,32)
        # mean = np.load(mean_file).mean(1).mean(1)
        # classifier = caffe.Classifier(deploy,caffe_model,image_dims = (32,32),mean = mean,raw_scale = 255,channel_swap = (2,1,0))
        classifier = caffe.Classifier(deploy,caffe_model,image_dims = (32,32),mean = mean,raw_scale = 255)
        return classifier

    net = load_model()

    with open(image_folder + '/test.list','r') as f:
        test_list = f.read().splitlines()

    groudtruth = [int(_.split()[-1]) for _ in test_list]
    test_list = [os.path.join(test_folder,o.split()[0]) for o in test_list]

    count = 0
    predict_result = []
    for i in xrange(len(test_list)):
        image = caffe.io.load_image(test_list[i])
        output_prob = net.predict([image])[0]
        predict_label = output_prob.argsort()[-1]

        if groudtruth[i] == predict_label:
            count += 1
        print 'test done.accuray:%.4f'%(1.0 * count / (i+1))


def visualFeatureMap():
    # for layer_name, blob in net.blobs.iteritems():
    #     print layer_name + '\t' + str(blob.data.shape)
    # for layer_name, param in net.params.iteritems():
        # print layer_name + '\t' + str(param[0].data.shape), str(param[1].data.shape)

    with open(image_folder + '/test.list','r') as f:
        test_list = f.read().splitlines()

    groudtruth = [int(_.split()[-1]) for _ in test_list]
    test_list = [os.path.join(test_folder,o.split()[0]) for o in test_list]
    for img in test_list:
        image = caffe.io.load_image(img)
        transformed_image = transformer.preprocess('data',image)
        net.blobs['data'].data[...] = transformed_image
        net.forward()
        feat = net.blobs['conv1'].data[:,:3].transpose(0,2,3,1)
        # print feat.shape
        vis_square(feat,'conv1_feature.jpg')
        exit()

# show_params()
# forward_batch()
# input_output()
# convert_meanfile()
# create_mean()
# use_solver()
# make_classifier()
# test1()
visualFeatureMap()
