#include<iostream>
#include <unistd.h>

using namespace std;
int main()
{
        long n=0;
        time_t start,finish;
        start=time(NULL);
        sleep(3);
//        while(n<1000000000)
//             n++;
        finish=time(NULL);
        std::cout<<(finish-start)<<std::endl;
        return 0;
}
