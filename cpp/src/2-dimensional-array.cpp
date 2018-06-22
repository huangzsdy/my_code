//二维数组的简单示例

#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

void  method1(int row,int col){
  int ** tmp = new int * [row];
  for(int i = 0;i < row;++i){
	tmp[i] = new int[col];
  }
  for(int k = 0;k < row;++k){
  	for(int j = 0;j < col;++j){
	    tmp[k][j] = rand() % 100;
            cout<<"tmp["<<k<<"]["<<j<<"] = "<<tmp[k][j]<<endl;
	}
  }
  cout<<*(tmp[0] + 1)<<endl;
  for(int i = 0;i < row;++i){
	 delete tmp[i];
         tmp[i] = NULL;
  }
}

void  method2(int row,int col){
   vector< vector<int> > tmp(row,vector<int>(col));
   for(int k = 0;k < row;++k){
	 for(int j = 0;j < col;++j){	
		tmp[k][j] = rand() % 10;
                cout<<"tmp["<<k<<"]["<<j<<"] = "<<tmp[k][j]<<endl;
	 }
   }
}

//如果是用引用的方式，则n重数组就n重指针的引用
void  method3(int **& tmp,int row,int col){
  cout<<1<<endl;
  tmp = new int * [row];
  cout<<2<<endl;
  for(int i = 0;i < row;++i){
	tmp[i] = new int[col];
  cout<<3<<endl;
  }
  for(int k = 0;k < row;++k){
        cout<<4<<endl;
  	for(int j = 0;j < col;++j){
	    tmp[k][j] = rand() % 100;
            cout<<"tmp["<<k<<"]["<<j<<"] = "<<tmp[k][j]<<endl;
	}
  }
  cout<<*(tmp[0] + 1)<<endl;
}

//如果是用指针的方式，则n重数组就n+1重指针
void  method4(int *** tmp,int row,int col){
  *tmp = new int * [row];
  for(int i = 0;i < row;++i){
	(*tmp)[i] = new int[col];
  }
  for(int k = 0;k < row;++k){
  	for(int j = 0;j < col;++j){
	    (*tmp)[k][j] = rand() % 100;
            cout<<"tmp["<<k<<"]["<<j<<"] = "<<(*tmp)[k][j]<<endl;
	}
  }
  cout<<*((*tmp)[0] + 1)<<endl;
}

//如果是用引用的方式，则n重数组就n重指针的引用
void  method5(int ** tmp,int row,int col){
  cout<<1<<endl;
  tmp = new int * [row];
  cout<<2<<endl;
  for(int i = 0;i < row;++i){
	tmp[i] = new int[col];
  cout<<3<<endl;
  }
  for(int k = 0;k < row;++k){
        cout<<4<<endl;
  	for(int j = 0;j < col;++j){
	    tmp[k][j] = rand() % 100;
            cout<<"tmp["<<k<<"]["<<j<<"] = "<<tmp[k][j]<<endl;
	}
  }
  cout<<*(tmp[0] + 1)<<endl;
}

int main(int argc,char ** argv){
  int row = atoi(argv[1]);
  int col = atoi(argv[2]);
  int ** input = NULL;
  method3(input,row,col);
  //method4(&input,row,col);
  //int * input = NULL;
  //method5(&input,row,col);
   
  for(int i = 0;i < row;i++){
     delete input[i];
     input[i] = NULL;
  }
  return 0;
}
