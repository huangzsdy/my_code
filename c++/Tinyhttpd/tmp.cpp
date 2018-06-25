#include <iostream>
using namespace std;

struct tmp {
  int a;
};
int main(int argc,char **argv){
    tmp a;
    a.a = 1;
    struct tmp * b = &a;
   
    cout<<a.a<<endl;
    cout<<((struct tmp *)&a)->a<<endl;
    return 0;
}
