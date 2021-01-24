// g++ $(pkg-config --cflags --libs opencv) -std=c++11 sharpening.cpp -o sharpening
#include "opencv2/opencv.hpp"
#include <iostream> 

using namespace cv;
using namespace std;

int main(){ 
    Mat img = imread("./images/Fig04moon.tif", 0); 
    Mat blurred, dst;
    blur(img, blurred, Size(7, 7)); 
    addWeighted(img, 2.0, blurred, -1.0, 0.0, dst); 
    imshow("org", img);
    imshow("blurred", blurred);
    imshow("shapen", dst);

    waitKey(0);
}