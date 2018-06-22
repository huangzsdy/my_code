#!/bin/bash
#用wget下图片
for line in `cat URL文件`;
do
         wget  -P tmp/ $line
done

