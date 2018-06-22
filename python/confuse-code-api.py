#coding:utf-8
import os

ori_folder = 'source-test'
des_folder = 'tmp'

import os
def gci(filepath,all_files):
#遍历filepath下所有文件，包括子目录
  files = os.listdir(filepath)
  for fi in files:
    fi_d = os.path.join(filepath,fi)            
    if os.path.isdir(fi_d):
      gci(fi_d,all_files)                  
    else:
      all_files.append(fi_d)


all_files = []

gci(ori_folder,all_files)
for i in all_files:
    new_place = i.replace(ori_folder,des_folder)
    if not new_place.endswith('.js'):
       continue
    if '/' in new_place:
        folder = new_place[:new_place.rfind('/')]
        if not os.path.isdir(folder):
           os.makedirs(folder)
    os.system('uglifyjs  {} -o {} '.format(i,new_place))
     
    
