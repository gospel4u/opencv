
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
	Mat img = imread("images/lenna_gray_400.tif", IMREAD_GRAYSCALE);
	Mat dst;

	Laplacian(img, dst, CV_16S);
	convertScaleAbs(dst, dst);

	imshow("Laplacian", dst);
	waitKey(0);
}


