#coding:utf-8

#opencv2的常用操作


import cv2


def readImage():
	#opencv 读图BGR
	#1
	img = cv2.imread('new.jpg',cv2.IMREAD_COLOR)
	print type(img),img.shape,img.size
	cv2.imwrite('new_COLOR.jpg',img)	#(h,w,c)
	#2
	img = cv2.imread('new.jpg',cv2.IMREAD_GRAYSCALE)
	print 'new_GRAYSCALE',type(img),img.shape,img.size #(h,w) 
	cv2.imwrite('new_GRAYSCALE.jpg',img)
	img1 = img
	#3
	img = cv2.imread('new.jpg',cv2.IMREAD_COLOR)
	img = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
	print type(img),img.shape,img.size
	cv2.imwrite('new_COLOR_BGR2GRAY.jpg',img)	#(h,w)
	img2 = img

	print img1 == img2	#2  == #3

	#4
	img = cv2.imread('new.jpg',cv2.IMREAD_COLOR)
	img = cv2.cvtColor(img,cv2.COLOR_BGR2HSV)
	print type(img),img.shape,img.size
	cv2.imwrite('new_COLOR_BGR2HSV.jpg',img)	#(h,w,c)


readImage()