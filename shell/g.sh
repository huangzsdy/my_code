#! /bin/bash

src_file=$1,des_file=$2
echo 'src_file:'$1,'des_file:'$2

if ! diff $src_file  $des_file > /dev/null ;
    echo $src_file $des_file 'same file !!!'
fi;

