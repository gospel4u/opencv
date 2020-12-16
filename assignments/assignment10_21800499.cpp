#include "opencv2/opencv.hpp"
#include <iostream> 

using namespace cv;
using namespace std;

int main() {
	Mat frame;
	VideoCapture cap("./images/background.mp4", 0);

	if (cap.open("./images/background.mp4") == 0) {
		cerr << "file open fail" << endl;
		return -1;
	}
	double fps = cap.get(CAP_PROP_FPS);
	int delay = 1000 / fps;
	int cnt = 10000;
	Mat background, foreground, img, gray, result, foregroundMask, foregroundimg;
	cap >> background;

	// Take a background image
	while (cap.get(CAP_PROP_POS_FRAMES) <= 10) {
		if (background.empty()) break;
		if (!cap.read(img)) break;
		add(img / cnt, background * (cnt - 1) / cnt, background);
		cnt++;
	}
	cvtColor(background, background, COLOR_BGR2GRAY);
	
	while (1) {
		cap >> foreground;
		if (foreground.empty()) {
			cerr << "empty frame" << endl;
			break;
		}
		cvtColor(foreground, foreground, COLOR_BGR2GRAY);
		absdiff(foreground, background, foregroundMask);
		threshold(foregroundMask, result, 20, 255, THRESH_BINARY);
		result.copyTo(foregroundimg);
		foreground.copyTo(foregroundimg, result);

		// Drawing the bounding rectangle of objects
		vector<vector<Point>> contours;
		vector<Vec4i>hierarchy;
		findContours(result, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

		// Defining bounding rectangle & draw rectangles on the contours
		vector<Rect> boundRect(contours.size());
		int countRect = 0;
		for (int i = 0; i < contours.size(); i++) {
			// Draw bounding rectangle on moving objects which size > 400
			if (boundingRect(Mat(contours[i])).area() > 400) {
				boundRect[i] = boundingRect(Mat(contours[i]));
				rectangle(foreground, boundRect[i].tl(), boundRect[i].br(), Scalar(255), 2, 8, 0);
				countRect++;	// take the number of moving objects which size > 400
			}
		}
		// Print out the number of moving objects which size > 400
		putText(foreground, format("# Rect: %d", countRect), Point(20, 40), FONT_HERSHEY_SIMPLEX, 1, Scalar(255), 4);

		// Show the output
		imshow("background subtraction", background);
		waitKey(delay);
		
	}
	return 0;
}