#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat img, hsv, smooth;
    img = imread("images/Fig06_lenna.tif", 1);
	
	imshow("org", img);
	blur(img, smooth, Size(11, 11));
	imshow("smooth (RGB)", smooth);

	cvtColor(img, hsv, COLOR_BGR2HSV);
	std::vector<Mat> channel(3);
	split(hsv, channel);

	blur(channel[2], channel[2], Size(11, 11));

	merge(channel, hsv);
	cvtColor(hsv, img, COLOR_HSV2BGR);
	imshow("V channel", img);

	waitKey(0);
}




