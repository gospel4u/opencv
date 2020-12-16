// g++ $(pkg-config --cflags --libs opencv) -std=c++11 image_log_trans.cpp -o image_log_trans
#include "opencv2/opencv.hpp"
#include <iostream> 

using namespace cv;
using namespace std;

void get_logTable(uchar lut[]);

int main(){
    Mat img = imread("./images/Fig03_DFT.tif", 0);
	uchar table[256];

	imshow("input", img);
	get_logTable(table);
	for (int i = 0; i < img.rows; i++)
		for (int j = 0; j < img.cols; j++)
			img.at<uchar>(i, j) = table[img.at<uchar>(i, j)];
	imshow("processed", img);
	waitKey(0);
}

void get_logTable(uchar lut[]){
	double rmax = 255;

	cout << "LOG transform Table " << endl;
	double C = 255.0 / log10(rmax + 1);
	for (int i = 0; i < 256; i++) {
		float v = C * log10((float)i + 1.0);
		lut[i] = saturate_cast<uchar>(v);
	}
}


