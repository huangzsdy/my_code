#include <iostream>  
using namespace std;  
  
/*
 * 成员的情况下是单参数的，调用对象是该类型本身，参数是传递的对象。比如a+b等价于a.operator+(b)。
 * 如果是友元，前者是调用参数是第一参数，后者是传递对象，第二参数。a+b就等价于operator+(a,b);
 */
class Point{  
public:  
    Point(int _x = 0, int _y = 0, int _z = 0):x(_x), y(_y), z(_z){}  
    Point(){}  
    ~Point(){}  
    friend ostream& operator<<(ostream &os, const Point &pd);  
    Point & operator+ (Point &);
private:  
    int x;  
    int y;  
    int z;  
};  
  
ostream& operator<<(ostream &os, const Point &pd){  
    os << pd.x<<" "<<pd.y<<" "<<pd.z;  
    return os;  
}  
   
Point& Point::operator+ (Point & tmp){
    x += tmp.x;
    y += tmp.y;
    z += tmp.z;
}
int main() {  
    Point pd(1,2,3);  
    cout<<pd<<endl;  
    Point qd(4,5,6);
    qd =  qd + pd;
    cout<<qd;
    return 0;  
} 
