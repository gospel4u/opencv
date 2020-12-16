#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat img = imread("images/lenna_gray_400.tif", 0);
	Mat dst;
	imshow("org", img);

	adaptiveThreshold(img, dst, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 19, 0);
	imshow("MEAN_C 19", dst);
	adaptiveThreshold(img, dst, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 19, 0);
	imshow("GAUSSIAN 19", dst);
	adaptiveThreshold(img, dst, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 49, 0);
	imshow("MEAN_C 49", dst);
	adaptiveThreshold(img, dst, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 49, 0);
	imshow("GAUSSIAN 49", dst);
	adaptiveThreshold(img, dst, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 199, 0);
	imshow("MEAN_C 199", dst);
	adaptiveThreshold(img, dst, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 199, 0);
	imshow("GAUSSIAN 199", dst);
	waitKey(0);
}



