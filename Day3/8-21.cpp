#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {

	Mat img = imread("images/Fig04_house.tif", 0);
	Mat deriv_X, deriv_Y;
	imshow("org", img);
	Sobel(img, deriv_X, CV_16S, 1, 0);
	Sobel(img, deriv_Y, CV_16S, 0, 1);

	convertScaleAbs(deriv_X, deriv_X); // 16S -> 8U
	convertScaleAbs(deriv_Y, deriv_Y); // 16S -> 8U

	imshow("Horiz_Derivative", deriv_X);
	imshow("Vertical_Derivative", deriv_Y);
	waitKey(0);
}
