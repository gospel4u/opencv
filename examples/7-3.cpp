
#include <iostream> 
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main() {
    Mat img, blurred, dst, mask;
	img = imread("images/Closing.png");
    resize(img, img, Size(0,0), 0.5, 0.5);
	if (img.empty())
		return -1;
	imshow("org", img);

	mask = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));

	morphologyEx(img, dst, MORPH_CLOSE, mask, Point(-1, -1), 2);
	imshow("close", dst);
    
	waitKey(0);
}
