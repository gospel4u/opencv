// g++ $(pkg-config --cflags --libs opencv) -std=c++11 histograme_show.cpp -o histograme_show

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void show_hist(Mat& img, char* wname);

int main(){
	Mat img = imread("./images/Fig03_pollen4.tif", 0);
	Mat dst;
	if (img.empty())
		return 0;
	imshow("org", img);
	show_hist(img, (char*)"input hist");

	equalizeHist(img, dst);
	imshow("eqlaized", dst);
	show_hist(dst, (char*)"dst hist");

	waitKey(0);
}

void show_hist(Mat& img, char* wname){
	Mat hist;
	float ranges[] = { 0, 255 };
	const float* histRange = { ranges };
	const int histSize[] = { 256 };
	bool uniform = true;
	bool accum = false;
	const int channels[] = { 0 };
	//const Mat img2 = img.clone();
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
			//			Scalar(0, 200, 100), CV_FILLED);
			Scalar(0, 200, 100), FILLED);
	}

	flip(histImg, histImg, 0);

	imshow(wname, histImg);
}