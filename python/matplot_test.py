#coding:utf-8
import matplotlib.pyplot as mpl
import numpy as np
from PIL import Image

def t0():
	x = range(10)
	y = [ i * i for i in x]
	mpl.plot(x,y)
	mpl.savefig('a.jpg')
	# mpl.show()


def t1():
	mpl.ion()
	x = np.linspace(0,50,1000)
	mpl.figure(1)
	mpl.plot(x,np.sin(x))
	mpl.draw()
	mpl.show()
	mpl.close()
	mpl.figure(2)
	mpl.plot(x,np.cos(x))
	mpl.draw()
	mpl.savefig('t1.jpg')

def t2():
	def f(t):  
		return np.exp(-t) * np.cos(2 * np.pi * t)  

	t1 = np.arange(0, 5, 0.1)  
	t2 = np.arange(0, 5, 0.02)  
	  
	mpl.figure(12)  
	mpl.subplot(221)  
	mpl.plot(t1, f(t1), 'bo', t2, f(t2), 'r--')  
	  
	mpl.subplot(222)  
	mpl.plot(t2, np.cos(2 * np.pi * t2), 'r--')  
	  
	mpl.subplot(212)  
	mpl.plot([1, 2, 3, 4], [1, 4, 9, 16])  
	  
	mpl.show() 

#画灰度图
def convert_to_gray_image():
	img = Image.open('new.jpg')
	gray = img.convert('L')
	mpl.figure('test.jpg')
	mpl.imshow(gray,cmap='gray')
	mpl.axis('off')
	mpl.show()

# 一张图有两y轴，一个x轴，可以把train_loss和acc放在一张图一块看
def plot_2():
	test_interval = 200
	test_acc = [ 0.1,0.41999999,0.47999999,0.54000002,0.62,0.63,
  0.64999998,0.66000003,  0.66000003,  0.67000002,  0.70999998,  0.69999999,
  0.75,        0.74000001,  0.76999998,  0.75,        0.69999999,  0.74000001,
  0.72000003,  0.76999998]
  	train_loss = test_acc[::-1]
  	_, ax1 = mpl.subplots()
	ax2 = ax1.twinx()
	ax1.plot(test_interval * np.arange(len(train_loss)), train_loss, 'b')
	ax2.plot(test_interval * np.arange(len(test_acc)), test_acc, 'r')
	ax1.set_xlabel('iteration')
	ax1.set_ylabel('train loss')
	ax2.set_ylabel('test accuracy')
	mpl.show()


if __name__ == '__main__':
	# convert_to_gray_image()	
	plot_2()