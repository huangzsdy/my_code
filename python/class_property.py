from decimal import Decimal

########################################################################
class Fees(object):
    """"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self._fee = None

    #----------------------------------------------------------------------
    @property
    def fee(self):
        """
        The fee property - the getter
        """
        return self._fee

    #----------------------------------------------------------------------
    @fee.setter
    def fee(self, value):
        """
        The setter of the fee property
        """
        if isinstance(value, str):
            self._fee = Decimal(value)
        elif isinstance(value, Decimal):
            self._fee = value

#----------------------------------------------------------------------
if __name__ == "__main__":
    f = Fees()
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
from decimal import Decimal
 
########################################################################
class Fees(object):#必须继承 object类，要不会报错
    """"""
 
    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self._fee = None
 
    #----------------------------------------------------------------------
    @property
    def fee(self):
        """
        The fee property - the getter
        """
        return self._fee
 
    #----------------------------------------------------------------------
#    @fee.setter
    def fee1(self, value):
        """
        The setter of the fee property
        """
        if isinstance(value, str):
            self._fee = Decimal(value)
        elif isinstance(value, Decimal):
            self._fee = value
 
#----------------------------------------------------------------------
if __name__ == "__main__":
    f = Fees()
    f.fee = ['2',2]#如果没有fee.setter，那默认就是只读的，所以不能直接赋值 
    print f.fee
