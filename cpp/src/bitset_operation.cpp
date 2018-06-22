#include <iostream>
#include <limits>
#include <bitset>

using namespace std;



int main(int argc,char ** argv){
	bitset<8> bs1(7);//10进制初始化7
	bitset<8> bs2(0x07);//16进制初始化7
	bitset<8> bs3("00000111");//字符串初始化7
	bitset<numeric_limits<unsigned short>::digits> bs4(267);//16位
	bitset<numeric_limits<unsigned long>::digits> bs5(267);//64位
	bitset<8> bs6;bs6[0] = 1;// 0000 0001
	string str("00011001101");
	bitset<8> bs7(str,1,3);bitset<8>bs8(str,str.size() - 4);

	cout<<bs1.to_string()<<" "<<bs2<<endl;
	cout<<bs3.to_string()<<" "<<bs4<<endl;
	cout<<bs5.to_string()<<" "<<bs6<<endl;
	cout<<bs7<<" "<<bs8<<endl;
	cout<<"---------"<<endl;
	cout<<bs1.any()<<endl;//是否存在值为1的二进制位
	cout<<bs1.none()<<endl;//是否不存在值为1的二进制位或者说是否全部位为0
	cout<<bs1.size()<<endl;//位长，也即是非模板参数值
	cout<<bs1.count()<<endl;//值为1的个数
	cout<<bs1.to_ulong()<<endl;//将二进制转换为unsigned long输出
	cout<<bs1.test(2)<<endl;//位数都是从右往左递增，和数组相反;测试pos处的二进制位是否为1与0做或运算
	//bs.flip()	全部位逐位取反;bs.flip(pos)	pos处的二进制位取反
	bs1.flip();cout<<bs1.to_string()<<" ";bs1.flip(1);cout<<bs1.to_string()<<endl;
	//bs.set()	全部位置1;bs.set(pos)	pos位处的二进制位置1与1做或运算
	//reset 正好相反。
	bs1.set(0);cout<<bs1.to_string()<<" ";bs1.set();cout<<bs1.to_string()<<endl;
	bs1.reset(0);cout<<bs1.to_string()<<" ";bs1.reset();cout<<bs1.to_string()<<endl;
	cout<<~bs1<<" "<<bs1<<endl;;//~bs和bs.flip()效果相同，返回反转后的bs
	return 0;
}