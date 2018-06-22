#!/bin/bash
#var=(a b c)
#for foo in ${var}
#do 
#  echo $foo
#done
#exit 0
echo "enter password:"
read pwd
while ["$pwd" != "root"]
do 
  echo "sorry,try again"
  read pwd
done
exit 0
