#include <iostream>
#include <algorithm>

using namespace std;
/*
** 贪心策略是：1.一定有一个最优解是以结束时间最早的节目为第一个节目的。2.每次选择剩下节目中结束时间最早的那个节目
*/
struct program {
	int startTime;
	int endTime;
	bool operator < (const program& A) const{
		return endTime < A.endTime;
	}
}buf[100];

int main(int argc,char ** argv){
	int currentTime(0),n(0),count(0);
	while(cin>>n){
		if(n == 0)
			break;
		for(int i = 0;i < n;++i){
			cin>>buf[i].startTime>>buf[i].endTime;
		}

		sort(buf,buf + n);//按照结束时间升序排列

		for(int j = 0;j < n; ++j){//已经升序排列，所以只要开始时间比currentTime晚就可以加入计数
			if(currentTime <= buf[j].startTime){
				currentTime = buf[j].endTime;
				++count;
			}
		}
	}
	
	cout<<"可以安排:"<<count<<"个节目"<<endl;

	return 0;
}