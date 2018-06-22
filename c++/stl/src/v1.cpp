#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

void output(int& a){
    cout << a <<" ";
}

int main(int argc, char**argv){
    int a[3] = { 1, 2, 4 };
    vector<int>v1(a, a + 3);
    vector<int>v2(5);
    vector<int>v3(10, 1);
    vector<int>v4(v2);
    
    //front back
    cout<<"v1.front() "<<v1.front()<<endl;
    cout<<"v1.back() "<<v1.back()<<endl;

    //fill
    int b[4];
    fill(b,b+4,10);
    for(int i = 0;i < 4;i++)
        cout<<b[i]<<endl;
    
    //copy 打印
    vector<int> v5;
    copy(a,a+3,back_inserter(v5));

    // assign 重新分配
    v4.assign(4, 2);//清除之前的数据，变成4个2
    
    //for_each
    for_each(v5.begin(), v5.end(), output);//第一种cout方法
    cout<<endl;
    
    copy(v1.begin(),v1.end(),ostream_iterator<int>(cout," "));//第二种cout 方法，需要#include <iterator>
    cout<<endl;

    v5.insert(v5.begin(),b,b+2);
    for_each(v5.begin(),v5.end(),output);
    cout<<endl;

    //insert
    v5.insert(v5.begin(),3,-1);
    copy(v5.begin(),v5.end(),ostream_iterator<int>(cout," "));
    cout<<endl;

    while(!v5.empty()){
        for_each(v5.begin(),v5.end(),output);
        cout<<endl;
        v5.pop_back();
    }

    v5.resize(10);//调用reserve(n)后，若容器的capacity<n，则重新分配内存空间，从而使得capacity等于n。如果capacity>=n呢？capacity无变化
    copy(v5.begin(),v5.end(),ostream_iterator<int>(cout," "));
    cout<<endl;
    cout<<"after resize,size:"<<v5.size()<<" capacity:"<<v5.capacity()<<endl;
    
    v5.reserve(15);//调用reserve(n)后，若容器的capacity<n，则重新分配内存空间，从而使得capacity等于n。如果capacity>=n呢？capacity无变化
    copy(v5.begin(),v5.end(),ostream_iterator<int>(cout," "));
    cout<<endl;
    cout<<"after reserve,size:"<<v5.size()<<" capacity:"<<v5.capacity()<<endl;

    v1.swap(v5);
    copy(v1.begin(),v1.end(),ostream_iterator<int>(cout," "));
    cout<<endl;
    for_each(v5.begin(),v5.end(),output);
    cout<<endl;

    v1.erase(v1.begin(),v1.end()-2);
    for_each(v1.begin(),v1.end(),output);
    cout<<endl;

    //reverse_iterator
    vector<int>::reverse_iterator rIter = v3.rbegin();
    while(rIter != v3.rend())
        cout<<*rIter++<<" ";
    cout<<endl;
}   
