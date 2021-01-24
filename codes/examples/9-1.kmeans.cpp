// g++ $(pkg-config --cflags --libs opencv) -std=c++11 9-1.kmeans.cpp -o 9-1.kmeans
#include "opencv2/opencv.hpp"
#include <iostream> 

using namespace cv;
using namespace std;

int main() {
	Mat src = imread("./images/coin_B2.jpg");
	float width = 500;
	float height = width * ((double)src.rows / (double)src.cols);
	resize(src, src, Size(width, height));
	imshow("original", src);

	blur(src, src, Size(5, 5));
	imshow("blurred", src);

	Mat p = Mat::zeros(src.cols * src.rows, 5, CV_32F);
	Mat bestLabels, centers, clustered;
	vector<Mat> bgr;
	cv::split(src, bgr);
	// i think there is a better way to split pixel bgr color
	for (int i = 0; i < src.cols * src.rows; i++) {
		p.at<float>(i, 0) = (i / src.cols) / src.rows;
		p.at<float>(i, 1) = (i % src.cols) / src.cols;
		p.at<float>(i, 2) = bgr[0].data[i] / 255.0;
		p.at<float>(i, 3) = bgr[1].data[i] / 255.0;
		p.at<float>(i, 4) = bgr[2].data[i] / 255.0;
	}

	int K = 2;
	cv::kmeans(p, K, bestLabels,
	TermCriteria(TermCriteria::Type::EPS | TermCriteria::Type::MAX_ITER, 10, 1.0),3, KMEANS_PP_CENTERS, centers);

	vector<Vec3b>  colors(K);
	for (int i = 0; i < K; i++) {
		colors[i] = Vec3b(rand() % 256, rand() % 256, rand() % 256);
	}
	// i think there is a better way to do this mayebe some Mat::reshape?
	clustered = Mat(src.rows, src.cols, CV_8UC3);
	for (int i = 0; i < src.cols * src.rows; i++) {
		int y = i / src.cols;
		int x = i % src.cols;
		clustered.at<Vec3b>(y, x) = colors[bestLabels.at<int>(i)];
	}

	//	clustered.convertTo(clustered, CV_8U);
	imshow("clustered", clustered);

	waitKey(0);

}