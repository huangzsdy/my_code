#coding:utf8

import socket
port = 12001
host = 'localhost'
sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
sock.sendto(b'nihao',(host,port))