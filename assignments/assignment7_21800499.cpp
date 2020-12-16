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
	Mat edge_left, edge_right, result;

	while (1) {
		cap >> frame;
		cap >> frame2;
		cap >> result;

		if (frame.empty() || frame2.empty()) {
			cerr << "empty frame" << endl;
			break;
		}
		double cur_frame = cap.get(CAP_PROP_POS_FRAMES);

		left_roi = frame(Rect(200, 400, 400, 200));
		right_roi = frame2(Rect(600, 400, 400, 200));
		
		// left_roi
		cvtColor(left_roi, gray_left, COLOR_RGB2GRAY);
		blur(gray_left, gray_left, Size(5, 5));
		Canny(gray_left, edge_left, 10, 60, 3);

		// right_roi
		cvtColor(right_roi, gray_right, COLOR_RGB2GRAY);
		blur(gray_right, gray_right, Size(5, 5));
		Canny(gray_right, edge_right, 10, 60, 3);

		// HoughLines
		vector<Vec2f> lines_left, lines_right;
		double rho = 0, rho2 = 0;
		float a, b, x0, y0;
		double theta = 0, theta2 = 0;
		double angle;
		Point p1, p2;
		int x1, x2, y1, y2;
		double rho_left_avg, theta_left_avg, rho_right_avg, theta_right_avg;
		double rho_total_left = 0, rho_total_right = 0;
		double theta_total_left = 0, theta_total_right = 0;
		int count_left = 0, count_right = 0;
		HoughLines(edge_left, lines_left, 1, CV_PI / 180, 120);
		for (int i = 0; i < lines_left.size(); i++) {
			rho = lines_left[i][0]; 
			theta = lines_left[i][1]; 
			angle = theta * 180 / CV_PI;
			if (angle > 30 && angle < 60) {
				a = cos(theta);
				b = sin(theta);
				x0 = a * rho;
				y0 = b * rho;
				
				rho_total_left += rho;
				theta_total_left += theta;
				count_left++;
			}
		}
		HoughLines(edge_right, lines_right, 1, CV_PI / 180, 120);
		for (int i = 0; i < lines_right.size(); i++) {
			rho2 = lines_right[i][0];
			theta2 = lines_right[i][1];
			angle = theta2 * 180 / CV_PI;
			if (angle > 120 && angle < 150) {
				a = cos(theta2);
				b = sin(theta2);
				x0 = a * rho2;
				y0 = b * rho2;
			
				rho_total_right += rho2;
				theta_total_right += theta2;
				count_right++;
			}
		}

		// take avarage of rho and theta
		rho_left_avg = rho_total_left / count_left;
		theta_left_avg = theta_total_left / count_left;
		rho_right_avg = rho_total_right / count_right;
		theta_right_avg = theta_total_right / count_right;

		// draw lines
		for (int i = 0; i < lines_left.size(); i++) { 
			a = cos(theta_left_avg);
			b = sin(theta_left_avg);
			x0 = a * rho_left_avg + 200;
			y0 = b * rho_left_avg + 400;
			p1 = Point(cvRound(x0 + 2000 * (-b)), cvRound(y0 + 2000 * a));
			p2 = Point(cvRound(x0 - 2000 * (-b)), cvRound(y0 - 2000 * a));
			line(result, p1, p2, Scalar(0, 0, 255), 3, 8);
		}
		
		for (int i = 0; i < lines_right.size(); i++) {
			a = cos(theta_right_avg);
			b = sin(theta_right_avg);
			x0 = a * rho_right_avg + 600;
			y0 = b * rho_right_avg + 400;
			p1 = Point(cvRound(x0 + 2000 * (-b)), cvRound(y0 + 2000 * a));
			p2 = Point(cvRound(x0 - 2000 * (-b)), cvRound(y0 - 2000 * a));
			line(result, p1, p2, Scalar(0, 0, 255), 3, 8);
		}
		
		imshow("Frame", result);
		waitKey(delay);

		if (cur_frame == cvRound(20 * fps)) {
			waitKey(0);
			break;
		}
	}
	return 0;
}