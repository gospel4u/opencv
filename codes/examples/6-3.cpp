#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void show_hist(Mat& img, char* wname);
int main () {
    Mat img = imread("images/Fig10_std_50.tif", IMREAD_GRAYSCALE);
	
    if (img.empty())
		return -1;

	imshow("org", img);

	Mat dst, deblurimg, deblurdst;
	blur(img, deblurimg, Size(5, 5));

	threshold(deblurimg, deblurdst, 0, 255, THRESH_OTSU);
	threshold(img, dst, 0, 255, THRESH_OTSU);

	show_hist(deblurimg, (char*)"deblurred hist");
	show_hist(img, (char*)"img hist");
	imshow("thresh_OTSU", dst);
	imshow("deblurred OTSU", deblurdst);

	waitKey(0);
}

void show_hist(Mat& img, char* wname) {
	Mat hist;
	float ranges[] = { 0, 255 };
	const float* histRange = { ranges };
	const int histSize[] = { 256 };
	bool uniform = true;
	bool accum = false;
	const int channels[] = { 0 };

	// compute histogram
	calcHist(&img, 1, channels, Mat(), hist, 1, histSize, &histRange, uniform, accum);

	double maxVal = 0;
	minMaxLoc(hist, 0, &maxVal, 0, 0);

	int scale = 2;
	Mat histImg = Mat::zeros(256 * scale, 256 * scale, CV_8UC3);

	for (int v = 0; v < 256; v++) {
		float binVal = hist.at<float>(v);
		int  num = cvRound(binVal * 255.0 / maxVal);

		rectangle(histImg, Point(v * scale, num * scale),
			Point((v + 1) * scale - 1, 0),
			Scalar(0, 200, 100), FILLED);
	}

	flip(histImg, histImg, 0);
	imshow(wname, histImg);
}
