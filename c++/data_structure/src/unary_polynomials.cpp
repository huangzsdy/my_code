/*
* 线性表实现一元多项式
* 利用线性表存储节点元素
*/
#include<iostream>
#include<cmath>
#define LIST_INIT_SIZE 100 //初始分配量
#define LISTINC 50 //增长量
using namespace std;

struct LNode{   //节点类
	double p;//系数项
	int  e;//指数项
};

struct SqList  //顺序存储线性表类
{
	SqList()
	{
	 elem = (LNode *)malloc(LIST_INIT_SIZE*sizeof(LNode));;
	 capacity = LIST_INIT_SIZE;
	 size = 0;
	 mx = 0;
	}
	LNode * elem;
	size_t size;//项数
	size_t capacity;//当前存储容量
	double mx;
};



//链表扩充函数
bool EnlargeList(SqList & list)
{
	
	list.elem = (LNode *)realloc(list.elem,(list.capacity + LISTINC)*sizeof(LNode));//一般来说，realloc的时候，如果连续内存足够大，则会返回相同的指针地址
	if(!list.elem )//如果不够大，则会重新申请一块足够大的内存，并返回指向这块内存的地址，所以list.elem要重新指向
	{
	   return false;
	}
	
	list.capacity += LISTINC;
	return true;
}

//初始化一元多项式线性表中的系数项、指数项
void InitList(SqList & list1,double ps[],int es[],int n)//ps代表系数项数组，es代表指数项数组,n代表该一元多项式的个数
{
	int i =0;
	for(;i<n;i++)
	{
		if(list1.size>=list1.capacity)
		{
			EnlargeList(list1);
		}
		list1.elem[list1.size].p = ps[i];
		list1.elem[list1.size].e = es[i];
		list1.size++;
	}
}

//计算该一元多项式结果
double GetResult(SqList & list1)
{
 double sum =0;
 for(size_t i=0;i<list1.size;i++)
 {
	 sum+= list1.elem[i].p*(pow(list1.mx,list1.elem[i].e));
 }
 return sum;
}

//清空一个一元多项式线性表
void clear(SqList & list1)
{
	list1.size = 0;
	//如果空间过大将空间进行压缩
	if(list1.capacity>LIST_INIT_SIZE)
	{
		free(list1.elem);
		list1.elem = (LNode *)malloc(LIST_INIT_SIZE*sizeof(LNode));;
		list1.capacity = LIST_INIT_SIZE;
		list1.size = 0;
		list1.mx = 0;
	}
}

int main()
{
 //建立一个线性表
	SqList myList;
	int n;
	cout<<"输入该一元多项式的项数："<<endl;
	cin>>n;
 //保存系数项和指数项
	double* ps = new double[n];//系数项
	int* es = new int[n];//指数项

 //输入数据
	int i = 0;
	cout<<"依次输入系数和对应指数，共";
	cout<<n<<"对"<<endl;
	while (i<n)
	{ cin>>ps[i]>>es[i];
	  i++;
	}
	cout<<"输入该一元多项式的变量x值"<<endl;
	cin>>myList.mx;

//初始化线性表
	InitList(myList,ps,es,n);

 //计算结果
	double s = GetResult(myList);
	i=0;
	for( i=0;i<int(myList.size-1);i++)
 {
	 cout<< myList.elem[i].p<<"*"<<myList.mx<<"^"<<myList.elem[i].e<<"+";
 }
	 cout<< myList.elem[i].p<<"*"<<myList.mx<<"^"<<myList.elem[i].e<<" = ";
	 cout<<s<<endl;
 return 0;
}