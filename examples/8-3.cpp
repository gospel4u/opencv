#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat getGradientMag(Mat& dev_X, Mat& dev_Y);
void thresholdGradientMag(Mat& mag, Mat& edges, int threshold);

int main () {
    Mat img = imread("images/Fig04_house.tif", 0);
	Mat dev_X, dev_Y, edges;
	imshow("org", img);

	Sobel(img, dev_X, CV_16S, 1, 0);
	Sobel(img, dev_Y, CV_16S, 0, 1);

	Mat gradient_mag = getGradientMag(dev_X, dev_Y);
	thresholdGradientMag(gradient_mag, edges, 100);
	imshow("edge", edges);

	waitKey(0);
}

Mat getGradientMag(Mat& dev_X, Mat& dev_Y) {
	Mat mag(dev_X.rows, dev_X.cols, CV_16S);

	for (int i = 0; i < dev_X.rows; i++)
		for (int j = 0; j < dev_X.cols; j++) {
			mag.at<short>(i, j) = abs(dev_X.at<short>(i, j)) + abs(dev_Y.at<short>(i, j));
		}

	return mag;
}

void thresholdGradientMag(Mat& mag, Mat& edges, int threshold) {
	edges = Mat::zeros(mag.size(), CV_8U);
    
	for (int i = 0; i < mag.rows; i++) {
        for (int j = 0; j < mag.cols; j++) {
            if (mag.at<short>(i, j) > threshold)
				edges.at<uchar>(i, j) = 255;
        }
    }		
}
