#include <iostream>
#include <algorithm>

using namespace std;

struct goods{
	float price;
	float weight;
	float f;
	bool operator < (const goods & A) const{
		return f > A.f;
	}
}buf[1000];

int main(int argc,char **argv){
	int kind;
	float allMoney,allGot;
	while(cin>>allMoney>>kind){
		if(kind == -1 && allMoney == -1){
			cerr<<"got -1"<<endl;
			break;
		}

		for(int i = 0;i < kind;i++){
			cin>>buf[i].weight>>buf[i].price;
			buf[i].f = buf[i].weight / buf[i].price;
		}

		sort(buf,buf+kind);

		int index = 0;

		while(allMoney > 0 && index < kind){
			if(allMoney >= buf[index].price){
				allMoney -= buf[index].price;
				allGot += buf[index].weight;
			}//如果能全部买下，就全买下,买不了就花光剩下的钱
			else{
				allGot += (buf[index].f * allMoney);
				allMoney = 0;
			}
			index++;
		}
	}
	cout<<"allGot:"<<allGot<<endl;
	return 0;
}