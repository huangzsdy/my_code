#coding:utf-8

def t1():
   def ISOString2Time( s ):  
   '''''  
    convert a ISO format time to second 
    from:2006-04-12 16:46:40 to:23123123 
    把一个时间转化为秒 
   '''  
       d=datetime.datetime.strptime(s,"%Y-%m-%d %H:%M:%S")  
       return time.mktime(d.timetuple())  
  
    def Time2ISOString( s ):  
    '''''  
    convert second to a ISO format time 
    from: 23123123 to: 2006-04-12 16:46:40 
    把给定的秒转化为定义的格式 
    '''  
       return time.strftime("%Y-%m-%d %H:%M:%S", time.localtime( float(s) ) ) 

    a="2013-08-26 16:58:00"  
    b=ISOString2Time(a)  
    print b  
    c=Time2ISOString(b)  
    print c 
t1()
