 //testRotateRect.cpp : 定义控制台应用程序的入口点。    
#include <opencv2/opencv.hpp>    
#include <iostream>
using namespace std;    
using namespace cv;    
int main(int argc,char* argv[])    
{    
         Mat image(200,200,CV_8UC3,Scalar(0));    
         RotatedRect rRect=RotatedRect(Point2f(100,100),Size2f(100,50),30); //定义一个旋转矩形    
         Point2f vertices[4];    
         rRect.points(vertices);//提取旋转矩形的四个角点    
         for(int i=0;i<4;i++)    
         {    
                  line(image,vertices[i],vertices[(i+1)%4],Scalar(0,255,0));//四个角点连成线，最终形成旋转的矩形。    
         }    
         imshow("ran",image);    
         waitKey();    
         return 0;    
}
