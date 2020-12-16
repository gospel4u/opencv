#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {

	Mat img = imread("images/Fig04_house.tif", 0);
	Mat deriv_X, deriv_Y, deriv_XY;
	imshow("org", img);
	Sobel(img, deriv_X, CV_16S, 1, 0);
	Sobel(img, deriv_Y, CV_16S, 0, 1);
	Sobel(img, deriv_XY, CV_16S, 1, 1);

	convertScaleAbs(deriv_X, deriv_X); // 16S -> 8U
	convertScaleAbs(deriv_Y, deriv_Y); // 16S -> 8U
	convertScaleAbs(deriv_XY, deriv_XY);

	threshold(deriv_X, deriv_X, 50, 255, THRESH_BINARY);
	threshold(deriv_Y, deriv_Y, 50, 255, THRESH_BINARY);
	threshold(deriv_XY, deriv_XY, 30, 255, THRESH_BINARY);
	imshow("Horiz_Derivative", deriv_X);
	imshow("Vertical_Derivative", deriv_Y);
	imshow("Vert+Horiz", deriv_XY);
	waitKey(0);
}
