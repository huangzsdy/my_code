#include <iostream>
#include <time.h>
#include <unistd.h>
using namespace std;

int main(){
   clock_t start,finish;
   long n =0;
   start = clock();
   //start = time(NULL);
   while(n<10000000000)
      n++;
   finish = clock();
   //finish = time(NULL);
   cout<<"cost time "<<(long)(finish - start)/CLOCKS_PER_SEC<<endl;
}
