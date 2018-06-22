#coding :utf-8

from socket import *
import sys,time
from multiprocessing.dummy import Pool as ThreadPoool

class Tcpclient:
    port = None
    def __init__(self,port):
        while True:
           try:
             self.client=socket(AF_INET, SOCK_STREAM)
             self.client.connect(('123.56.40.175',port))
             st = time.time()
             data1 = 'data'
             while True:
                self.client.sendall(data1.encode('utf8'))
#        self.client.shutdown(socket.SHUT_WR)
                data2 = self.client.recv(1024)
                print 'get result from remote',time.time() - st
                if  data2:
                  print 'data2',data2
                  print data2.decode('utf8')
             self.client.close()
             break
             time.sleep(1)
           except Exception,e:
             #break
             pass

def socket_test(img):
    #print 'start',img
    client = socket(AF_INET,SOCK_STREAM)
    #client.connect(('123.56.40.175',17770))
    client.connect(('123.56.40.175',20012))
    st =  time.time()
    try:
     client.sendall(img)
     #print 'send',img
     result = client.recv(1024)
    # client.shutdown(socke.SHUT_WR)
     print 'get return',len(result),'time cost',time.time() - st
    except timeout:
        print 'timeout'
        pass
    client.close()

if __name__ == '__main__':
#    port = int(sys.argv[1])
    import random
    imgs = ['/home/faceall/ad/ocr_test/tmp/1493952986500fsjkS.jpeg']*2
    imgs = ['/local/data/yunjingwang-api-data/temp/1494472064133g8rza.jpg'] * 10
    imgs = ['/local/data/yunjingwang-api-data/temp/upload_cc7520ed22038d63d8d62b746567f66a.jpg']* 100
    #imgs = [str(random.randrange(1,100)) for i in xrange(10)]
    imgs = ['/home/faceall/ad/ocr_test/tmp/1494834237118z2mdZ.jpg']*100
    print len(imgs)
    for img in imgs:
         socket_test(img)
    #pool = ThreadPoool(2)
    #pool.map(socket_test,imgs)
    #pool.join()
    #pool.close()
