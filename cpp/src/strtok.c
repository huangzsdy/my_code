/* strtok example */ 
#include <stdio.h> 
#include <string.h> 

int main () 
{ 
    char str[] ="a,b,c,d*e"; 
    const char * split = ","; 
    char * p; 
    p = strtok (str,split); 
//    while(p!=NULL) { 
        printf ("%s\n",p); 
//        p = strtok(NULL,split); 
//    } 
    p = strtok (NULL,split);
    printf("%s\n",p);

    getchar(); 
    return 0; 

} 

