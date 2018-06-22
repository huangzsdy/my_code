#include <iostream>
using namespace std;
int main(int argc,char **argv)
{
   char * words[3] = {"nihao","woqu","ca"};
   char * ps[3];
   for (int j = 0;j<3;j++)
    { 
       ps[j] = words[j];
           }
   for (int k =0;k<3;k++)
     cout<<ps[k];
}
   
