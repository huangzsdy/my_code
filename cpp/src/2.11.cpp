#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
/*
** 解法：
** 1.为了方便，申请s[n+1][n+1]的数组，其中0列和0行不处理（打印的时候比较符合正常从1开始数，减少混乱）
** 2.可以注意到若是n行，则有(n+1)/2圈，相当于画(n+1)/2圈，从里向外画圈，则最里边下标为 k=(n+1)/2，因为是向外扩张着画圈，所以k是递减的，直到k=1
** 3.假设 k=b,画一个圈时，一般从s[b][b]开始画，根据对角线对称，每次可以画4个点（里层的for循环），至s[b][n+1-b]停止。即b~(n+1-b)
** 4.最后再去掉四个角
*/
int main()
{
    int n,k,i,j;
    char in_char,out_char;

    while(cin>>n>>in_char>>out_char && ((n>0 && n<80) && n%2!=0))
    {
        char s[n+1][n+1];
        memset(s,'0',sizeof s);

        char fill_char;
        int flag=0;           // flag用来记录框数的奇偶
        for(k=(n+1)/2;k>=1;--k)
        {
            flag++;
            if(flag%2==1) fill_char=in_char;
            else if(flag%2==0) fill_char=out_char; 

            cout<<"k:"<<k<<" fill_char:"<<fill_char<<endl;

            for(i=k;i<=n+1-k;i++)   //画图可知是根据对角线对称的四个点
            {
                s[k][i]=fill_char;
                s[i][k]=fill_char;               
                s[i][n+1-k]=fill_char;         
                s[n+1-k][i]=fill_char;        
                cout<<"i:"<<i<<" n+1-k:"<<(n+1-k)<<" s["<<k<<"]["<<i<<"] "<<" s["<<i<<"]["<<k<<"] "<<" s["<<i<<"]["<<n+1-k<<"] s["<<n+1-k<<"]["<<i<<"] "<<endl;
            }
            cout<<"----"<<endl;
        }      
        if(n!=1)     //去掉四个角
        {
            s[1][1]=' ';
            s[n][1]=' ';
            s[1][n]=' ';
            s[n][n]=' ';
        }      
        for(i=1;i<=n;i++)
        {
            for(j=1;j<=n;j++)
            {
                cout<<s[i][j];
            }
            cout<<endl;
        }      
        cout<<endl;
    }  
    return 0;
}


