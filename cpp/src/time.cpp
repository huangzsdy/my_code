#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>

/*
 * 1.linux 下的微秒计时
 * 2.windows 下的秒计时
 * 3.windows 下的毫秒计时
 */
void linuxCountTime1(){
    printf("Hello, world!\n");
    struct timeval tvafter,tvpre;
    struct timezone tz;
    int sum = 0;      
    int i=0;
    gettimeofday (&tvpre , &tz);

    // for(i = 0; i < 100000000; i++)
    // {
    //          sum += i;
    // }      
    sleep(2.7);//2.7会被取整成2秒
    gettimeofday (&tvafter , &tz);
    printf("sum=%d 花费时间:%d\n",sum, (tvafter.tv_sec-tvpre.tv_sec)*1000+(tvafter.tv_usec-tvpre.tv_usec)/1000); //gettimeofday tv_usec是微妙,tv_sec是秒
}

void linuxCountTime2(){
    printf("Hello, world!\n");
    int sum = 0;      
    int i=0;

    time_t start,stop;
    start = time(NULL);
    sleep(2);
    stop = time(NULL);
    printf("Use Time:%ld\n",(stop-start));
    // for(i = 0; i < 100000000; i++)
    // {
    //          sum += i;
    // }      
}

/*windows 下秒计时
void windowsCountTime1(int n){
//#include <time.h> windows 计时和Sleep

     int a;
     time_t st,et;
     st = time(NULL);
     Sleep(n * 1000);
     et = time(NULL);
     printf("%d\n",(et - st));
}
*/
/*windows 下毫秒计时
//#include <time.h> windows 计时和Sleep
 * void windowsCountTime2(int n){ 
 *  	clock_t st, et;
	st = clock();
	Sleep(210);
	et = clock();
	cout<< " cin 耗时:" << (et - st) << endl;     
 * }
 */




int main(int argc, char *argv[])
{
    linuxCountTime2();   
    return EXIT_SUCCESS;
}
