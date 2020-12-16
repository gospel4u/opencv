#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat img = imread("images/Fig06_lenna.tif", 1);
	Mat hsv, filtered, rgb_filtered;
	imshow("org", img);
	vector<Mat> rgb_ch(3);
    std::vector<Mat> channel(3);
	split(img, rgb_ch);

	for (int i = 0; i < 3; i++) {
		Laplacian(rgb_ch[i], filtered, CV_16S);
		convertScaleAbs(filtered, filtered);
		rgb_ch[i] = rgb_ch[i] + 1.5 * filtered;
	}
    
	merge(rgb_ch, rgb_filtered);
	imshow("Laplacian (RGB)", rgb_filtered);

	cvtColor(img, hsv, COLOR_BGR2HSV);
	split(hsv, channel);
	
	Laplacian(channel[2], filtered, CV_16S);
	convertScaleAbs(filtered, filtered);
	channel[2] = channel[2] + 1.5 * filtered;
	
	merge(channel, hsv);
	cvtColor(hsv, img, COLOR_HSV2BGR);
	imshow("Laplacian(HSV)", img);

	waitKey(0);
}
