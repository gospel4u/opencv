// g++ $(pkg-config --cflags --libs opencv) -std=c++11 resize.cpp -o resize
#include "opencv2/opencv.hpp"
#include <iostream> 

using namespace cv;
using namespace std;
 
int main(void){
    Mat src = imread("./images/web.jpg");
     
    imshow("before", src);
    cout << src.rows << " " << src.cols << endl;
 
    Mat dst;
    resize(src, dst, Size(256, 256), 0, 0, CV_INTER_LINEAR);
    imshow("after", dst);
    cout << dst.rows << " " << dst.cols << endl;
    waitKey();
    return 0;
}

