#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat img, blurred, dst, mask;
	img = imread("images/Fig04_fingerprint.tif");
    resize(img, img, Size(0,0), 0.5, 0.5);
	imshow("org", img);

	mask = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
	dilate(img, dst, mask);
	imshow("Dilate", dst);
	erode(img, dst, mask);
	imshow("erode", dst);
    
	waitKey(0);
}

