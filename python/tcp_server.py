#coding:utf-8

from  socket import *
from time import ctime

host = '0.0.0.0'
port = 20012
sock = socket(AF_INET,SOCK_STREAM)
sock.bind((host,port))
sock.listen(5)
while True:
    print ('waiting for conection')
    tcpclientsock, addr = sock.accept()
    print('connect from',addr)
   # while True:
   #     try :
   #         data = tcpclientsock.recv(1024)
   #     except:
   #         print e
   #         tcpclientsock.close()
   #         break
   #     if not data:
   #         break
    data = tcpclientsock.recv(1024)
    s = 'hi,nihao:[%s] %s ' %(ctime(),data.decode('utf8'))
    tcpclientsock.send(s.encode('utf8'))
    print [ctime(),':',data.decode('utf8')]
    tcpclientsock.close()
sock.close()

