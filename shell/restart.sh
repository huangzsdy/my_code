#!/bin/sh

# restart server 

source ./env.sh

ROOTDIR=`pwd`
PORTS=5000

while true
do
  for port in $PORTS
  do  
      result=`netstat -alnp | grep $port`
      if [ -z "$result" ];then
          echo $result
          echo server $base down !!
          nohup python -u server.py > result.log &
      fi
  done
  sleep 1
done

