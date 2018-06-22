#include <iostream>
#include <stdlib.h>
using namespace std;

int main(int argc,char ** argv){
	int height = atoi(argv[1]);
	for(int i = 1;i <= height; i++){
		for(int k = 1;k <= (3*height - 2);k++ ){
			if(k <= (2*(height - i)))
				cout<<" ";
			else
				cout<<"*";
		}
		cout<<endl;
	}
	return 0;
}