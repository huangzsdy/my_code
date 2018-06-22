#include <iostream> 
using namespace std;
int main(){
    char * p [] = {"-d--","cdf","@S"};
    char ** ptr = p;
    for(int i=0;i<3;i++){
    cout<<"ptr="<<ptr<<endl;

    cout<<"*ptr="<<*ptr<<endl;
    cout<<"**ptr="<<**ptr<<endl;
    ptr++;
    }
 }

