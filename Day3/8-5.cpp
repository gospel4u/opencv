#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main() {
	Mat dst;
	Mat img = imread("images/lenna_gray_400.tif", IMREAD_GRAYSCALE);
	imshow("input", img);
	Canny(img, dst, 70, 180);
	imshow("Canny", dst);

	Mat gaussian_noise = img.clone();
	randn(gaussian_noise, 0, 20);
	dst = img + gaussian_noise;
	imshow("N", dst);

	Mat edge;
	Canny(dst, edge, 70, 180);
	imshow("Noise Canny", edge);

	waitKey(0);
}

