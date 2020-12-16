#include <iostream>
#include "opencv.hpp"
using namespace std;
using namespace cv;

Mat get_HorizDerivKernel() {
	Mat kernel = (Mat_<float>(3, 3) << -1, 0, 1, -1, 0, 1, -1, 0, 1);
	kernel = kernel / 3.0;
	return kernel;
}

Mat get_VertDerivKernel() {
	Mat kernel = (Mat_<float>(3, 3) << -1, -1, -1, 0, 0, 0, 1, 1, 1);
	kernel = kernel / 3.0;
	return kernel;
}

int main() {
	Mat dst;
	Mat img = imread("images/Fig04_house.tif", IMREAD_GRAYSCALE);
	Mat horiz_kernel = get_HorizDerivKernel();
	Mat vert_kernel = get_VertDerivKernel();
	Mat deriv_X, deriv_Y;

	std::cout << horiz_kernel << std::endl;
	std::cout << vert_kernel << std::endl;

	filter2D(img, deriv_X, CV_16S, horiz_kernel);
	filter2D(img, deriv_Y, CV_16S, vert_kernel);

	convertScaleAbs(deriv_X, deriv_X); // 16S -> 8U
	convertScaleAbs(deriv_Y, deriv_Y); // 16S -> 8U

	imshow("Horiz_Derivative", deriv_X);
	imshow("Vertical_Derivative", deriv_Y);

	waitKey(0);
}
