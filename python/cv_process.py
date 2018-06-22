#coding:utf-8

import cv2

#flipped

def flipped(image):
    img = cv2.imread(image)
    return img[:,::-1,:]
