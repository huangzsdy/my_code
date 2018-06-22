#include <iostream>
using namespace std;

void HeapSort(int arr[],int n){
	int i,j,k,t;
	i = n/2 - 1;//第一个非叶节点
	for(;i>=0;i--){
		while(2*i+1 < n){ //有左子数
			j = 2*i + 1;
			if(j + 1 < n){//有右子树
				if(arr[j] < arr[j+1])
					j++;
			}
			if(arr[i] < arr[j]){
				t = arr[i];
				arr[i] = arr[j];
				arr[j] = t;
				i = j;
			}
			else
				break;
		}
	}
	cout<<"after first heap sort ..."<<endl;
	for(int m = 0;m < n;m++)
		cout<<arr[m]<<" ";
	cout<<endl;
	for(i = n-1;i>=0;i--){
		t = arr[i];
		arr[i] = arr[0];
		arr[0] = t;
		k = 0;
		while(2*k + 1 < i){
			j = 2*k+1;
			if(j + 1 < i){
				if(arr[j] < arr[j+1])
					j++;
			}
			if(arr[k] < arr[j]){
				t = arr[k];
				arr[k] = arr[j];
				arr[j] = t;
				k = j;
			}
			else
				break;
		} 
	}
}

int main(int argc,char** argv){
	const int size = 8;
	int tmp[size] = {67,65,77,38,97,3,33,49};
	HeapSort(tmp,size);
	for(int i = 0;i < size;++i)
		cout<<tmp[i]<<" ";
	return 0;
}