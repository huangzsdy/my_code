import caffe

import numpy as np
from PIL import Image
import random

class imageBatch(caffe.Layer):
    def setup(self,bottom,top):
        """ 
        Setup data layer according to parameters: 
 
        - image_list: image path with label
        - batch_size: number of images per batch 
        - mean: tuple of mean values to subtract 
        - shuffle: shuffle image_list (default: True) 
 
 
        example 
 
        params = dict(image_list="/path/to/your list", 
            mean=(104.00698793, 116.66876762, 122.67891434), 
            shuffle="false") 
        """  
        # config  
        params = eval(self.param_str)
        self.image_list = params['image_list']
        self.batch_size = params['batch_size']
        self.mean = np.array(params['mean'])
        self.crop_size = params['crop_size']
        self.idx = 0
        self.next_idx = 0
        self.shuffle = params['shuffle'].lower() == 'true'
        self.indices = open(self.image_list,'r').read().splitlines()

        if self.shuffle:
            random.shuffle(self.indices)


        # two tops: data and label  
        if len(top) != 2:  
            raise Exception("Need to define two tops: data and label.")  
        # data layers have no bottoms  
        if len(bottom) != 0:  
            raise Exception("Do not define a bottom.") 
        if self.batch_size > len(self.indices):
            raise Exception("batch size has to be smaller than length of list.")


    def reshape(self,bottom,top):
        if self.idx + self.batch_size >= len(self.indices):
            self.next_idx = (self.idx + self.batch_size) % len(self.indices)
            batch = np.concatenate((self.indices[self.idx:],self.indices[:self.next_idx]),axis=0)
        else:
            self.next_idx = (self.idx + self.batch_size)
            batch = self.indices[self.idx:self.next_idx]
        self.data = self.load_images(batch)
        self.label = self.load_labels(batch)

        top[0].reshape(*self.data.shape)
        top[1].reshape(*self.label.shape)


    def forward(self,bottom,top):
        top[0].data[...] = self.data
        top[1].data[...] = self.label

        self.idx = self.next_idx
        print 'forward self.idx:',self.idx

    def backward(self,top,propagate_down,bottom):
        pass

    def load_images(self,batch):
        """ 
        Load input image and preprocess for Caffe: 
        - resize 
        - cast to float 
        - switch channels RGB -> BGR 
        - subtract mean 
        - transpose to channel x height x width order 
        """  
        images = []
        for line in batch:
            img = line.split()[0]
            im = Image.open(img)
            im = im.resize(self.crop_size)
            in_ = np.array(im,dtype=np.float32)
            in_ = in_[:,:,::-1]
            in_ -= self.mean
            in_ = in_.transpose((2,0,1))
            
            images.append(in_)

        return np.array(images)

    def load_labels(self,batch):
        labels = np.array([line.split()[-1] for line in batch])
        labels.reshape(self.batch_size,1)
        return labels
