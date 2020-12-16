// g++ $(pkg-config --cflags --libs opencv) -std=c++11 smoothing.cpp -o smoothing
#include "opencv2/opencv.hpp"
#include <iostream> 

using namespace cv;
using namespace std;

int main() {
	Mat img = imread("./images/Fig04_characters_test.tif", 0);
	Mat blurred, dst;
	if (img.empty())
		return 0;
	imshow("Output", img);
	char title[20];
	for (int i = 5; i < 20; i += 6) {
		blur(img, blurred, Size(i, i));
		sprintf(title, "mean %d", i);
		imshow(title, blurred);

		medianBlur(img, blurred, i);
		sprintf(title, "median %d", i);
		imshow(title, blurred);

		GaussianBlur(img, blurred, Size(i, i), 0, 0);
		sprintf(title, "Gaussian %d", i);
		imshow(title, blurred);

		bilateralFilter(img, blurred, i, i * 2, i / 2);
		sprintf(title, "bilateral %d", i);
		imshow(title, blurred);
	}
	waitKey(0);
}