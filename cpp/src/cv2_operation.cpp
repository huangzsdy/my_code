#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int main(int argc,char ** argv){
	cv::Mat image = cv::imread(argv[1]);
    cout<<"cols:"<<image.cols<<" rows:"<<image.rows<<endl;
	cv::Point x1_y1(10,10);
	cv::Point x2_y2(100,100);
	cv::rectangle(image,x1_y1,x2_y2,cv::Scalar(0,0,255));
	cv::imwrite("a.jpg",image);
	return 0;
}
