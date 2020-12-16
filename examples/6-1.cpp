#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {

    Mat img, dst;
    img = imread("images/lenna_gray_400.tif", 0);

	imshow("org", img);
	threshold(img, dst, 100, 255, THRESH_BINARY);
	imshow("BINARY", dst);
	threshold(img, dst, 100, 255, THRESH_BINARY_INV);
	imshow("INV", dst);
	threshold(img, dst, 100, 255, THRESH_TRUNC);
	imshow("TRUNC", dst);
	threshold(img, dst, 100, 255, THRESH_TOZERO);
	imshow("TOZERO", dst);
	waitKey(0);
}


