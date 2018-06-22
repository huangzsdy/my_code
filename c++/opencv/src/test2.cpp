#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/core.hpp>
//#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include "operation.hpp"

using namespace std;
using namespace cv;
void salt(Mat &image, int n ); //椒盐噪声产生函数
int main(int argc,char ** argv)
{
    struct timeval tvafter,tvpre;
    struct timezone tz;

    //
    Mat src; Mat dst;Mat help;

    /// Load the source image
    src = imread(argv[1], IMREAD_COLOR);
    help = src;
    Size size1(256,256);    
    Size size2(224,224);    
    gettimeofday (&tvpre , &tz);
    for (int i = 0;i < 128;++i){
      resize(src,dst,size1);
      resize(dst,src,size2);
      src = help;
    }
    gettimeofday (&tvafter , &tz);
    cout<<"time cost:";
    cout<<((tvafter.tv_sec-tvpre.tv_sec)*1000+(tvafter.tv_usec-tvpre.tv_usec)/1000); //毫秒

    return 0;
}
