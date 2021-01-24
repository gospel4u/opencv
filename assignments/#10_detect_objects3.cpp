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
	int num_frame_avg = 10;
	int cnt = 0;
	Mat background, foreground, result, foregroundMask, result_c;
	Mat element = getStructuringElement(MORPH_CROSS, Size(5, 5));
	Mat element_dilate = getStructuringElement(MORPH_DILATE, Size(15, 15));
	Mat element_erode = getStructuringElement(MORPH_ERODE, Size(5, 5));
	cap >> background;
	vector<Rect> found;

	cvtColor(background, background, COLOR_BGR2GRAY);
	Mat avg = Mat(background.rows, background.cols, CV_8UC1, Scalar(0));
	add(background / num_frame_avg, avg, avg);

	HOGDescriptor hog(Size(48, 96), Size(16, 16), Size(8, 8), Size(8, 8), 9);
	hog.setSVMDetector(HOGDescriptor::getDaimlerPeopleDetector());

	CascadeClassifier body_classifier;
	body_classifier.load("./data/haarcascade_fullbody.xml");

	
	while (1) {
		cap >> foreground;
		if (foreground.empty()) {
			cerr << "empty frame" << endl;
			break;
		}
		resize(foreground, foreground, Size(500, 400));
		cvtColor(foreground, foreground, COLOR_BGR2GRAY);

		// Take a background image for first 10 frames
		if (cnt < 10) {
			if (background.empty()) break;
			add(background / num_frame_avg, avg, avg);
			cnt++;
		}
		else {
			resize(background, background, Size(500, 400));
			absdiff(foreground, background, foregroundMask);
			GaussianBlur(foregroundMask, foregroundMask, Size(3, 3), 0, 0, 4);
			threshold(foregroundMask, result, 45, 255, THRESH_BINARY_INV);

			/*body_classifier.detectMultiScale(
				result, found, 1.3, 1
			);*/
			hog.detectMultiScale(result, found, 0, Size(4, 4), Size(16, 16), 1.5);

			// drawresults(boundingboxes)
			int countRect = 0;
			cout << found.size() << endl;
			for (int i = 0; i < found.size(); i++) {
				Point lb(found[i].x + found[i].width, found[i].y + found[i].height);
				Point tr(found[i].x, found[i].y);
				rectangle(foreground, lb, tr, Scalar(255), 2, 4, 0);
				countRect++;
			}
			// Drawing the bounding rectangle of objects
			/*vector<vector<Point>> contours;
			vector<Vec4i>hierarchy;
			findContours(result_c, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);*/

			// Defining bounding rectangle & draw rectangles on the contours
			//vector<Rect> boundRect(contours.size());
			////int countRect = 0;
			//for (int i = 0; i < contours.size(); i++) {
			//	// Draw bounding rectangle on moving objects which size > 600
			//	if (boundingRect(Mat(contours[i])).area() > 600 && found.size() > 0) {
			//		boundRect[i] = boundingRect(Mat(contours[i]));
			//		rectangle(foreground, boundRect[i].tl(), boundRect[i].br(), Scalar(255), 2, 8, 0);
			//		countRect++;	// take the number of moving objects which size > 600
			//	}
			//}
			// Print out the number of moving objects which size > 600
			putText(foreground, format("# The number of people: %d", countRect), Point(20, 40), FONT_HERSHEY_SIMPLEX, 1, Scalar(255), 3);

			// Show the output
			imshow("Number of people", foreground);
		}
		waitKey(delay);
	}
	waitKey(0);

	return 0;
}