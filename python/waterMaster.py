#-*- coding:utf-8 -*-
import PIL
from PIL import Image
from PIL import ImageDraw
from PIL import ImageFont
from random import choice
from random import randint
from random import sample
from random import uniform
import os
import time

import sys  
reload(sys)  
sys.setdefaultencoding('utf8') 

# windows 版的给图片加水印，其中drawWaterMark2加透明水印
# 在windows中路径记得加r
#设置所使用的字体
size = 20
font = ImageFont.truetype("C:\Windows\Fonts\STXIHEI.ttf", size)

oriFolder = r"C:\Users\hzs\Desktop\lfw"
desFolder = r"C:\Users\hzs\Desktop\result"
cropFolder = r"C:\Users\hzs\Desktop\crop_result"

charToText1 = ['1','2','3','4','5','6','7','8','9','0']
charToText2 = [u'嘉我',u'微芯',u'加我',u'微信','QQ','qq',u'加Q',u'电话','Q',u'加']

#result.lst 是框的坐标和文本内容；crop_result.lst是截图后的文本内容

# 在图上添加水印字体，但没法添加透明水印
def drawWaterMark(imgName):
	imageFile = os.path.join(oriFolder,imgName)
	im1 = Image.open(imageFile)

	draw = ImageDraw.Draw(im1)

	x = randint(0,im1.size[0]/2)
	for i in xrange(0,im1.size[1]/2,size):	
		y = i
		draw.text((x,y), " ".join(sample(charToText,2)),fill=(255, 255, 255,0),font=font)   #设置文字位置/内容/颜色/字体
		draw.rectangle((x,y,x + size + 8,y + size),outline = "red")

	draw = ImageDraw.Draw(im1)                        
	im1.save(os.path.join('result',imgName))

# 可以添加透明水印
def drawWaterMark2(imgName):
	imageFile = os.path.join(oriFolder,imgName)

	im1 = Image.open(imageFile).convert('RGBA')
	txt = Image.new('RGBA',im1.size,(255,255,255,0))
	draw = ImageDraw.Draw(txt)

	x = randint(6,im1.size[0]/2)
	for i in range(6,im1.size[1]/4 * 3,size)[::3]:	
		y = i
		tmp = randint(0,10)
		if tmp % 2 == 0:
			charText = " ".join(sample(charToText1,2))
			draw.text((x,y),charText,fill=(255, 255, 255,255),font=font)   #设置文字位置/内容/颜色/字体
			# draw.rectangle((x - 6,y - 6,x + 32,y + 32),outline = "red")
			print>>fp1,imgName,x - 6,y - 6,x + 32,y + 32,str(charText)
		elif tmp % 2 == 1:
			charText = choice(charToText2)
			draw.text((x,y),charText,fill=(255, 255, 255,255),font=font)   #设置文字位置/内容/颜色/字体
			# draw.rectangle((x - 6,y - 6,x + 44,y + 40),outline = "red")
			print>>fp1,imgName,x - 6,y - 6,x + 44,y + 40,charText


	out = Image.alpha_composite(im1, txt)
	out.save(os.path.join(desFolder,imgName))
	
# 指定框旋转后crop
def cropRect(line):
	imgName = line.split()[0]
	coords = [int(o) for o in line.split()[1:5]]
	center_x = (coords[0] + coords[2])/2
	center_y = (coords[1] + coords[3])/2
	imageFile = os.path.join(desFolder,imgName)

	im1 = Image.open(imageFile).crop(tuple(coords))

	# 每个小图旋转10次
	for i in xrange(10):
		angle = uniform(-5,5)
		im2 = im1.rotate(angle)
		im2.save(os.path.join(cropFolder,str(angle) + '_' + imgName))
		print>>fp2,str(angle) + '_' + imgName," ".join(line.split()[5:])

if __name__ == '__main__':
	# fp1 = open('result.lst','w')
	# for img in os.listdir(oriFolder):
	# 	drawWaterMark2(img)
	# fp1.close()
	fp2 = open('crop_result.lst','w')
	for line in open('result.lst','r'):
		cropRect(line)
	fp2.close()
