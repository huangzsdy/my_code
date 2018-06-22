#coding:utf-8

import urllib2

# request = urllib2.request('http:www.baidu.com')
request=urllib2.Request('http://www.douban.com')
response = urllib2.urlopen(request)
print response.read()
