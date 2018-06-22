#coding:utf-8
''''' 
信号量semaphore 
是一个变量，控制着对公共资源或者临界区的访问。信号量维护着一个计数器，指定可同时访问资源或者进入临界区的线程数。 
每次有一个线程获得信号量时，计数器-1。若计数器为0，其他线程就停止访问信号量，直到另一个线程释放信号量。 
'''  
import threading  
import random  
import time  
  
class MyThread(threading.Thread):  
    availableTables=['A','B','C','D','E']  
      
    def __init__(self,threadName,semaphore):  
        self.interval =random.randrange(1,6)  
        self.semaphore =semaphore  
        threading.Thread.__init__(self,name=threadName)  
      
    def run(self):  
        self.semaphore.acquire()  
        #acquire a semaphore  
        table = MyThread.availableTables.pop()  
        print "%s entered;seated at table %s." %(self.getName(),table)  
        time.sleep(self.interval)  
          
        #free a table  
        print "%s exiting,freeing table %s." %(self.getName(),table)  
        MyThread.availableTables.append(table)  
          
        self.semaphore.release()  
  
mySemaphore = threading.Semaphore(len(MyThread.availableTables))  
  
def Test():       
    threads=[]  
      
    for i in range(1,10):  
        threads.append(MyThread("thread"+str(i),mySemaphore))  
      
    for i in range(len(threads)):  
        threads[i].start()  
  
if __name__ == '__main__':  
    Test() 
