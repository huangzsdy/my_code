#ifndef OPENCV_OPRATION_
#define OPENCV_OPRATION_

using namespace cv;
void salt(Mat& image, int n) {
    for (int k = 0; k<n; k++) {
        int i = rand() % image.cols;
        int j = rand() % image.rows;

        if (image.channels() == 1) {   //判断是一个通道
            image.at<uchar>(j, i) = 255;
        }
        else {
            image.at<cv::Vec3b>(j, i)[0] = 255;
            image.at<cv::Vec3b>(j, i)[1] = 255;
            image.at<cv::Vec3b>(j, i)[2] = 255;
        }
    }
}
#endif
