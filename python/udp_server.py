# coding:utf8

import socket
port = 12001
sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
sock.bind(('',port))
print('正在等待...')
while True:
    data,addr = sock.recvfrom(1024)
    print ('Received:',data,'from',addr)
