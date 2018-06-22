#include <iostream>
using namespace std;

template<class T> class A{
    public:
        T g(T a,T b);
        A();
};


template<class T> A<T>::A(){}

template<class T> T A<T>::g(T a,T b){
    return a+b;
}

template class A<float>;

int main(){
    A<int> a;
    cout<<a.g(2,3.2)<<endl;
}
