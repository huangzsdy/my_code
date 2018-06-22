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
    Mat src; Mat dst;

    /// Load the source image
    src = imread(argv[1], IMREAD_COLOR);
    salt(src, 30000);
    dst = src.clone();
//    medianBlur(src, dst, 3);
    GaussianBlur(src,dst,Size(3,3),0);
    string window_origin = "Origin";
    string window_median = "Median";
    imshow(window_origin, src);
    imshow(window_median, dst);
    waitKey(0);

    return 0;
}
