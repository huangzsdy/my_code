#!/bin/bash
dir=`ls`
for i in $dir
do 
  cat $i|while read line
  do 
    str1=echo $i|cut -d ' ' -f 1
    str2=echo $i|cut -d ' ' -f 2
    str3=echo $i|cut -d ' ' -f 3
    str4=echo $i|cut -d ' ' -f 4
    path=$str1+$str2
    mkdir path&&cd path
    ffmpeg -i '../$str1' -ss $str3 -vframes 10 %d.jpg
  done
done
