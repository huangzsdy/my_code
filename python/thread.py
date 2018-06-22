#coding:utf-8
import threading,time

def test(o):
    print o

def test2():
    print 2
ts = []
for i in xrange(1,15):
    th = threading.Thread(target = test,args = i)
    ts.append(th)
for j in (ts):
    j.start()
print time.strftime('%H:%M:%S')
