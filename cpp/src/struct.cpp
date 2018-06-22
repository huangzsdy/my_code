#include <iostream>

using namespace std;


int main(){
    struct human {
        int sex;
        int age;
    };
    human x[] = {{1,2},{3,4},{5,6}},*p=NULL;
    for(int i=0;i<3;i++){
        cout<<x[i].sex<<endl;
        cout<<x[i].age<<endl;
    }
    cout<<"----"<<endl;
    for(p=x;p<=(x+2);p++){
        cout<<p->sex<<endl;
        cout<<p->age<<endl;
    }

}
