#include <iostream>
using namespace std;

#define OFFSET (50000)

int main(int argc,char **argv){
	int n,m;
	int count[100000] = {0};
	int tmp;
	while(cin>>n>>m){
		if(!(n >= m)){
			cout<<"n is smaller than m "<<endl;
			return -1;
		}

		for(int i=0;i<n;i++){
			cin>>tmp;
			count[tmp+OFFSET] = 1;
		}

		for(int i=50000;i>-50000;i--){
			// if(m > 0){		
			// 	if(count[i+OFFSET] == 1){
			// 		cout<<i<<" ";
			// 		m--;
			// 	}
			// }
			// else
			// 	break;
			if(count[i+OFFSET] == 1){
				if(m > 0){
					cout<<i<<" ";
					m--;
				}
				else
					break;
			}
		}
	}
	return 0;
}