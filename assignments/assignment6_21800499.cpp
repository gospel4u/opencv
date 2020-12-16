#include "opencv2/opencv.hpp"
#include <iostream> 

using namespace cv;
using namespace std;

int main() {
	Mat frame, frame2;
	VideoCapture cap("./images/Road.mp4");

	if (cap.open("./images/Road.mp4") == 0) {
		cerr << "file open fail" << endl;
		return -1;
	}
	double fps = cap.get(CAP_PROP_FPS);
	int delay = 1000 / fps;
	Mat left_roi, right_roi;
	Mat gray_left, gray_right;
	Mat canny_left, canny_right;

	while (1) {
		cap >> frame;
		cap >> frame2;
		if (frame.empty() || frame2.empty()) {
			cerr << "empty frame" << endl;
			break;
		}
		
		left_roi = frame(Rect(200, 400, 400, 200));
		right_roi = frame2(Rect(600, 400, 400, 200));

		// left_roi
		cvtColor(left_roi, gray_left, COLOR_BGR2GRAY);
		blur(gray_left, gray_left, Size(5, 5));
		Canny(gray_left, canny_left, 10, 60, 3);

		// right_roi
		cvtColor(right_roi, gray_right, COLOR_BGR2GRAY);
		blur(gray_right, gray_right, Size(5, 5));
		Canny(gray_right, canny_right, 10, 60, 3);
		

		namedWindow("Left canny");
		moveWindow("Left canny", 200, 0);
		namedWindow("Right canny");
		moveWindow("Right canny", 600, 0);

		
		imshow("Left canny", canny_left);
		imshow("Right canny", canny_right);

		waitKey(delay);
	}
	return 0;
}