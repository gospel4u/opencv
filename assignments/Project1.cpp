#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat negative_trans(Mat src) {
	vector<Mat> channel(3);
	cvtColor(src, src, COLOR_BGR2HSV);
	split(src, channel);

	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			channel[2].at<uchar>(i, j) = 255 - channel[2].at<uchar>(i, j);

			if (channel[2].at<uchar>(i, j) > 255) channel[2] = 255;
			else if (channel[2].at<uchar>(i, j) < 0) channel[2] = 0;
			else channel[2].at<uchar>(i, j) = channel[2].at<uchar>(i, j);
		}
	}
	merge(channel, src);
	cvtColor(src, src, COLOR_HSV2BGR);
	return src;
}

Mat gamma_trans(Mat src) {
	vector<Mat> channel(3);
	cvtColor(src, src, COLOR_BGR2HSV);
	split(src, channel);
	/* Gamma transformation
	s = c * r ^ gamma (c = 255.0, gamma = 2.5) */
	float gamma = 2.5;

	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			channel[2].at<uchar>(i,j) = 255.0 * pow(float(channel[2].at<uchar>(i,j)) / 255.0, gamma);
		}
	}

	merge(channel, src);
	cvtColor(src, src, COLOR_HSV2BGR);

	return src;
}

Mat histogram_equal(Mat src) {
	vector<Mat> channel(3);
	cvtColor(src, src, COLOR_BGR2HSV);
	split(src, channel);

	equalizeHist(channel[2], channel[2]);

	merge(channel, src);

	cvtColor(src, src, COLOR_HSV2BGR);
	return src;
}


Mat color_slicing(Mat src) {
	Mat hsv, dst;
	cvtColor(src, hsv, COLOR_BGR2HSV);
	vector<Mat> channel(3);
	split(hsv, channel);

	for (int i = 0; i < hsv.rows; i++) {
		for (int j = 0; j < hsv.cols; j++) {
			if (channel[0].at<uchar>(i,j) <= 9 
				|| channel[0].at<uchar>(i,j)>= 23) 
				channel[1].at<uchar>(i,j) = 0;
		}
	}

	merge(channel, hsv);
	cvtColor(hsv, dst, COLOR_HSV2BGR);
	return dst;
}

Mat color_conversion(Mat src) {
	Mat hsv, dst;
	int cal = 0, norm = 0, cal2 = 0;
	cvtColor(src, hsv, COLOR_BGR2HSV);
	vector<Mat> channel(3);
	split(hsv, channel);

	for (int i = 0; i < hsv.rows; i++) {
		for (int j = 0; j < hsv.cols; j++) {
			norm = channel[0].at<uchar>(i, j);
			cal = channel[0].at<uchar>(i, j) + 50;
			cal2 = channel[0].at<uchar>(i, j) - 129;
			if (norm > 129)
				channel[0].at<uchar>(i, j) = cal2;
			else channel[0].at<uchar>(i, j) = cal;
		}
	}
	
	merge(channel, hsv);
	cvtColor(hsv, dst, COLOR_HSV2BGR);
	return dst;
}

Mat average_filtering(Mat src) {
	blur(src, src, Size(9, 9));
	return src;
}

Mat white_balancing(Mat src) {
	Mat dst;
	int b_avr = 0, g_avr = 0, r_avr = 0;
	int b_cal = 0, g_cal = 0, r_cal = 0;
	vector<Mat> channel(3);
	split(src, channel);

	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			b_avr += channel[0].at<uchar>(i, j);
			g_avr += channel[1].at<uchar>(i, j);
			r_avr += channel[2].at<uchar>(i, j);
		}
	}

	b_avr = b_avr / (src.rows * src.cols);
	g_avr = g_avr / (src.rows * src.cols);
	r_avr = r_avr / (src.rows * src.cols);

	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			b_cal = channel[0].at<uchar>(i, j) * (128.0 / b_avr);
			g_cal = channel[1].at<uchar>(i, j) * (128.0 / g_avr);
			r_cal = channel[2].at<uchar>(i, j) * (128.0 / r_avr);
			
			if (b_cal > 255)
				channel[0].at<uchar>(i, j) = 255;
			else channel[0].at<uchar>(i, j) = b_cal;
			if (g_cal > 255)
				channel[1].at<uchar>(i, j) = 255;
			else channel[1].at<uchar>(i, j) = g_cal;
			if (r_cal > 255)
				channel[2].at<uchar>(i, j) = 255;
			else channel[2].at<uchar>(i, j) = r_cal;
		}
	}

	merge(channel, dst);
	return dst;
}


int main() {
	Mat lena = imread("./images/lena.png", 1);
	Mat colorful = imread("./images/colorful.jpg", 1);
	Mat balancing = imread("./images/balancing.jpg", 1);

	if (lena.empty() || colorful.empty() || balancing.empty()) {
		cout << "load image fail" << endl;
		exit(1);
	}

	Mat lena_reset = lena.clone();
	Mat colorful_reset = colorful.clone();
	Mat balancing_reset = balancing.clone();

	// Show images
	char key;
	imshow("lena", lena);
	imshow("colorful", colorful);
	imshow("balancing", balancing);

	do {
		cout << "\n\tProject 1 Commands:" << endl;
		cout << "\tn - Negative transformation\t";		cout << "\tg - Gamma transformation\n";
		cout << "\th - Histogram equalization\n";		
		cout << "\ts - Color slicing\t\t";				cout << "\tc - Color conversion\n";
		cout << "\ta - Average filtering\t\t";			cout << "\tw - White balancing\n";
		cout << "\tr - Reset all images\n";
		cout << "\tCommand(Esc to quit): ";
		
		key = waitKey(0);
		
		switch (key) {
			case 'n':
				cout << "Negative transformation: \n";
				lena = negative_trans(lena);
				imshow("lena", lena);
				break;
			case 'g': 
				cout << "Gamma transformation: \n";
				lena = gamma_trans(lena);
				imshow("lena", lena);
				break;
			case 'h':
				cout << "Histogram eaulization: \n";
				lena = histogram_equal(lena);
				imshow("lena", lena);
				break;
			case 's':
				cout << "Color slicing: \n";
				colorful = color_slicing(colorful);
				imshow("colorful", colorful);
				break;
			case 'c':
				cout << "Color conversion: \n";
				colorful = color_conversion(colorful);
				imshow("colorful", colorful);
				break;
			case 'a':
				cout << "Average filtering: \n";
				balancing = average_filtering(balancing);
				imshow("balancing", balancing);
				break;
			case 'w':
				cout << "White balancing: \n";
				balancing = white_balancing(balancing);
				imshow("balancing", balancing);
				break;
			case 'r':
				cout << "Reset all images: \n";
				lena = lena_reset.clone();
				colorful = colorful_reset.clone();
				balancing = balancing_reset.clone();
				imshow("lena", lena);
				imshow("colorful", colorful);
				imshow("balancing", balancing);
				break;
			default:
				break;
		}
	} while (key != 27);
	return 0;
}

