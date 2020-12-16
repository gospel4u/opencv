#include "opencv2/opencv.hpp"
#include <iostream> 

using namespace std;
using namespace cv;

int main() {
    Mat img, blurred, dst, mask;
	img = imread("images/opening.png");
    resize(img, img, Size(0,0), 0.5, 0.5);

	imshow("org", img);

	mask = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
    
	morphologyEx(img, dst, MORPH_OPEN, mask, Point(-1, -1), 2);
	imshow("open", dst);
    
	waitKey(0);
}

