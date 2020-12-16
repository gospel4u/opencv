// g++ $(pkg-config --cflags --libs opencv) -std=c++11 gaussian.cpp -o gaussian
#include "opencv2/opencv.hpp"
#include <iostream> 

using namespace cv;
using namespace std;

int main() {
	Mat img = imread("./images/lena.png", 0);
	Mat dst;
	if (img.empty())
		return 0;
	imshow("Output", img);

	GaussianBlur(img, dst, Size(7, 7), 1.0, 1.0);
	imshow("1.0", dst);
	GaussianBlur(img, dst, Size(7, 7), 2.0, 2.0);
	imshow("2.0", dst);
	GaussianBlur(img, dst, Size(7, 7), 3.0, 3.0);
	imshow("3.0", dst);
	GaussianBlur(img, dst, Size(7, 7), 4.0, 4.0);
	imshow("4.0", dst);
	waitKey(0);
}

// void print_Gaussian(double size, double sigma) {

// 	Mat kernel = getGaussianKernel(size, sigma);
// 	int row = kernel.rows;
// 	int col = kernel.cols;
// 	if (kernel.isContinuous()) {
// 		col = col * row;
// 		row = 1;
// 	}

// 	cout << "Gaussian Kernel size=" << size << " sigma= " << endl;

// 	for (int i = 0; i < row; i++) {
// 		double* row_ptr = kernel.ptr<double>(i);
// 		for (int j = 0; j < col; j++)
// 			cout << row_ptr[j] << "  ";
// 		cout << endl;
// 	}
// }