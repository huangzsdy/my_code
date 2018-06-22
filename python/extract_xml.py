#coding:utf-8
#用来提取xml文件
import xml.etree.cElementTree as ET
import os

foldpath = '/home/tmp_data_dir/huangzesang/1051/xingren/walkman/TRAIN/ANNOTATIONS_TRAIN/'
xmls =[foldpath+one for one in os.listdir(foldpath)]

fp = open('train.txt','w')

def get_info(xml):
    if not xml.getchildren():
        if  xml.text == 'NULL' or xml.text.isdigit():
            fp.write(xml.text + ' ')
    else:
        for i in xml.getchildren():
            get_info(i)

for filename in xmls:
    tree = ET.parse(filename)
    root = tree.getroot()
    for one in root.getchildren():
        if one.tag == 'filename':
           fp.write(one.text + ' ')
        else:
           get_info(one)
    fp.write('\n')
#    get_info(root)
