/* 8-4.cpp */

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

static Mat input_img, edge_img;
static const char* win_name = "Canny";
static int lowThreshold, highThreshold;

void CannyThreshold(int, void*) {
	Canny(input_img, edge_img, lowThreshold, highThreshold, 3);
	imshow(win_name, edge_img);
}

int main() {
	input_img = imread("images/Fig04_house.tif", 0);
	edge_img.create(input_img.size(), input_img.type());

	GaussianBlur(input_img, input_img, Size(3, 3), 10, 10);

	namedWindow(win_name, WINDOW_AUTOSIZE);
	createTrackbar("Threshold1", win_name, &lowThreshold, 200, CannyThreshold);
	createTrackbar("Threshold2", win_name, &highThreshold, 255, CannyThreshold);

	waitKey(0);
}


