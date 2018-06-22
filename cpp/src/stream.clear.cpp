#include <iostream>  
#include <sstream>  
#include <string>  
using namespace std;  
int main()    
{  //clear（）很好解决复用问题但内存消耗大  
    int size = 100;    
    stringstream strStream;    
    for (int i = 1; i < size; ++i)    
    {    
        strStream.clear();  
        strStream << i;    
        string numStr;    
        strStream >> numStr;    
        cout<<numStr<<" ";   
        // strStream.str("");  如果没有这句，stringstream 占用的空间并不会因为clear而释放，久而久之会变得很大，所以每次需要重新写入之前需要用空字符串清空缓存区
    }                           //而clear的作用在于stringstream在一次>>和<<（或者反过来）之后，能复位标志位，使之重复可用。
    cout<<endl;  
    cout<<"stringstream size: "<<strStream.str().size()<<endl;  
    return 0;    
}    