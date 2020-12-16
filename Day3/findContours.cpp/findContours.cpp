// g++ $(pkg-config --cflags --libs opencv) -std=c++11 find_con.cpp -o find_con
#include "opencv2/opencv.hpp"
#include <iostream> 

using namespace cv;
using namespace std;

int main(){
	Mat src = imread("./images/bird.png", 1);
	Mat gray;

	Mat canny;
	GaussianBlur(src, src, Size(7, 7), 1.5, 1.5);
	Canny(src, canny, 80, 130);
	dilate(canny, canny, Mat(), Point(-1, -1), 2);
	imshow("Canny", canny);

	//find contours
	int cnt = 0;
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(canny.clone(), contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	if ((cnt = contours.size()) <= 0) {
		cout << "No components" << endl;
		return 0 ;
	}

	Mat result = src.clone();
	for (size_t i = 0; i < cnt; i++)
	{
		Scalar color(rand() % 256, rand() % 256, rand() % 256);
		drawContours(result, contours, i, color, -1);
	}

	imshow("src", src);
	imshow("result", result);
	waitKey(0);
	destroyAllWindows();
}

