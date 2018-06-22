#include <iostream>
#include <iomanip>
using namespace std;

/*
 * c++ cout 格式化输出
*/
int main(){
  double  d = 12.156;
  cout<<setprecision(4)<<d<<endl;//共有四位数，在这即为保留两位小数，四舍五入,12.16
  cout << setprecision(4) << 12.345678 << endl;//12.35
  cout <<setfill('0') ;//设置补全的字符
  cout <<setw(5) <<12 <<endl ;//00012
  return 0;
}
