#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat img = imread("images/Fig06_strawberry.tif", 1);
    Mat hsv, enhanced; 
    imshow("original img", img);

    cvtColor(img, hsv, COLOR_BGR2HSV); 
    std::vector<Mat> channels(3); 
    split(hsv, channels);
    
    channels[2] = 0.7 * channels[2]; 
    merge(channels, enhanced);
    cvtColor(enhanced, enhanced, COLOR_HSV2BGR); 
    
    imshow("darken", enhanced);
    waitKey(0);
}


