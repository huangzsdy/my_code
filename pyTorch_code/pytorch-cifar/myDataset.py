import os
import torch
import torch.utils.data as data
from PIL import Image
from multiprocessing.dummy import Pool
import numpy as  np

def default_loader(path):
    return Image.open(path).convert('RGB')

class myImageFolder(data.Dataset):
    def __init__(self, root, label,classes,transform = None, target_transform=None, loader=default_loader):        
        with open(label,'r') as f:
            fh = f.read().splitlines()
        imgs=[]
        pool_ = Pool(20)
        for line in fh:
            pool_.apply_async(self.load_one_image,(root,line,imgs))
        pool_.close()
        pool_.join()
        print 'load {} images done'.format(len(imgs))

        self.root = root
        self.imgs = imgs
        self.classes = list(classes)
        self.transform = transform
        self.target_transform = target_transform
        self.loader = loader

    def __getitem__(self, index):
        fn, label = self.imgs[index]
        img = self.loader(os.path.join(self.root, fn))
        if self.transform is not None:
            img = self.transform(img)
        return img, torch.Tensor(label)

    def __len__(self):
        return len(self.imgs)

    def getName(self):
        return self.classes

    def load_one_image(self,root,line,imgs):
        cls = line.split()
        fn = cls.pop(0)

        if os.path.isfile(os.path.join(root, fn)):
            imgs.append((fn, np.array([float(v) for v in cls],dtype=np.int64)))