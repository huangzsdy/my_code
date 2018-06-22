#类外可以通过_classname_spam来访问实例的私有成员_spam
class test(object):
  def __init__(self):
     self.data = 1
     self.__data = []
  def add(self,item):
     self.__data.append(item)
  def printData(self):
     print self.__data
t = test()
t.add('adfd')
t.add('efee')
t.printData()
print t._test__data
