// g++ $(pkg-config --cflags --libs opencv) -std=c++11 image_gamma.cpp -o image_gamma
#include "opencv2/opencv.hpp"
#include <iostream> 

using namespace cv;
using namespace std;

Mat apply_gamma_transform(Mat& gray, double gamma);
void get_logTable(uchar lut[]);
void prepare_lut(unsigned char lut[], float fGamma, float C);

int main() {
	Mat img, gray;
	unsigned char lut1[256], lut2[256], log_lut[256];
	gray = imread("./images/Fig03_pollen4.tif");

	if (gray.empty())
		return 0;

	Mat T = apply_gamma_transform(gray, 0.2);
	Mat T2 = apply_gamma_transform(gray, 2.5);
	get_logTable(log_lut);

	Mat table3(1, 256, CV_8UC1, lut2);
	Mat T3 = gray.clone();

	LUT(gray, table3, T3);

	imshow("org gray", gray);
	imshow("gamma=0.2", T2);
	imshow("gamma=2.5", T3);
	imshow("log", T);
	waitKey(0);
	destroyAllWindows();
}

Mat apply_gamma_transform(Mat& gray, double gamma) {
	unsigned char lut[256];

	prepare_lut(lut, gamma, 1);
	Mat table(1, 256, CV_8UC1, lut);
	Mat T = gray.clone();
	LUT(gray, table, T);
	return T;
}

void get_logTable(uchar lut[])
{
	double rmax = 255;

	cout << "LOG transform Table " << endl;
	double C = 255.0 / log10(rmax + 1);
	for (int i = 0; i < 256; i++) {
		float v = C * std::log10((float)i + 1.0);
		lut[i] = saturate_cast<uchar>(v);
	}
}

void prepare_lut(unsigned char lut[], float fGamma, float C)
{
	cout << "Gamma Transform Table" << endl;
	float max = 0;
	for (int i = 0; i < 256; i++) {
		float v = pow((float)(i / 255.0), fGamma) * 255.0f * C;
		lut[i] = saturate_cast<uchar>(v);
		cout << i << ':' << v << ':' << (int)lut[i] << endl;
	}

}