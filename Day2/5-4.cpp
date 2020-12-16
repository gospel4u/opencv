#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat img, hsv, enhanced;

    img = imread("images/Fig06_flower.tif", 1);
	resize(img, img, Size(0,0), 0.5, 0.5);
	imshow("org", img);

	cvtColor(img, hsv, COLOR_BGR2HSV);
	std::vector<Mat> channel(3);
	split(hsv, channel);
	equalizeHist(channel[2], channel[2]);
	merge(channel, enhanced);

	cvtColor(enhanced, enhanced, COLOR_HSV2BGR);
	imshow("enhanced", enhanced);

	waitKey(0);
}


