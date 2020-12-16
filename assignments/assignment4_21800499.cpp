#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat drawHistogram(Mat src, int histSize);
Mat draw_elements(Mat src, int histSize);


int main() {
	Mat img = imread("./images/moon.png", 0);
	Mat hist_equalized;
	Mat hist_graph, hist_equalized_graph;
	Mat before, after;

	if (!img.data) exit(1); //check img;

	equalizeHist(img, hist_equalized);

	hist_graph = drawHistogram(img, 16);
	hist_equalized_graph = drawHistogram(hist_equalized, 16);
	
	before = draw_elements(img, 8);
	after = draw_elements(hist_equalized, 8);

	float total_before = 0;
	float total_after = 0;

	for (int i = 0; i < 8; i++) {
		total_before += before.at<float>(i);
		total_after += after.at<float>(i);
	}

	for (int i = 0; i < 8; i++) {
		putText(img, format("bin %d: %f", i+1, before.at<float>(i) / total_before),
			Point(80, 80 + 20*i), FONT_HERSHEY_SIMPLEX, 0.5,
			Scalar(255, 0, 0), 2);

		putText(hist_equalized, format("bin %d: %f", i+1, after.at<float>(i) / total_after),
			Point(80, 80 + 20 * i), FONT_HERSHEY_SIMPLEX, 0.5,
			Scalar(255, 0, 0), 2);
	}

	imshow("before", img);
	imshow("after", hist_equalized);
	imshow("h1", hist_graph);
	imshow("h2", hist_equalized_graph);

	waitKey(0);
	return 0;
}

Mat drawHistogram(Mat src, int histSize) {
	Mat hist, histimage;

	int i, hist_w, hist_h, bin_w;
	//int histSize;
	float range[] = { 0, 256 };
	const float* histRange = { range };

	hist_w = 512;
	hist_h = 512;
	//histSize = 16;
	bin_w = cvRound((double)hist_w / histSize);

	histimage = Mat(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255));

	//compute the histogram
	calcHist(&src, 1, 0, Mat(), hist, 1, &histSize, &histRange);

	//normalize
	normalize(hist, hist, 0, histimage.rows, NORM_MINMAX, -1, Mat());

	for (i = 0; i < histSize; i++) {
		rectangle(histimage, Point(bin_w * i, hist_h),
			Point(bin_w * i + hist_w/histSize, hist_h - cvRound(hist.at<float>(i))),
			Scalar(0, 0, 0), -1);
	}

	return histimage;
}

Mat draw_elements(Mat src, int histSize) {
	Mat hist, histimage;

	int i, hist_w, hist_h, bin_w;
	//int histSize;
	float range[] = { 0, 256 };
	const float* histRange = { range };

	hist_w = 512;
	hist_h = 512;
	//histSize = 8;
	bin_w = cvRound((double)hist_w / histSize);

	histimage = Mat(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255));

	//compute the histogram
	calcHist(&src, 1, 0, Mat(), hist, 1, &histSize, &histRange);

	//normalize
	normalize(hist, hist, 0, histimage.rows, NORM_MINMAX, -1, Mat());

	return hist;
}
