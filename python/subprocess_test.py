#coding:utf-8

import subprocess
import time

class Server:
	def __init__(self):
		self._process = None
	def start(self):
		cmd = 'python  tmp.py'.split()
		self._process =subprocess.Popen(cmd,stdout=subprocess.PIPE,stderr=subprocess.PIPE,shell=False)
		# con = self._process.comm()
		# print cont
		lines_iterator = iter(self._process.stdout.readline,b'')#这句话采用迭代器，可以不断地去获得子进程的输出（按顺序）
		for line in lines_iterator:
			print '----'
			print line
			return 'sdfsdf'  #如果没有return ，就会一直卡死，在等待子进程的输出，知道子进程死掉

	def stop(self):
		print 'try to kill ',self._process.pid
		self._process.kill()
		com = self._process.communicate()
		print 'stopped',com



if __name__ == '__main__':
	server = Server()
	server.start()
	time.sleep(3)
	print 'sleep done'
	server.stop()
