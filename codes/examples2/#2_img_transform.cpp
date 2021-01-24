#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;


int main() {
	Mat img = imread("./images/lena.png", 0);

	/* negative transformation
		s = (L-1) - r	*/
	Mat negative_img = 255 - img.clone();	

	/* log transformation
		s = c * log(1+r) <- c = 1.5	 */
	Mat log_img;
	img.convertTo(log_img, CV_32F);
	log_img += 1;
	log(log_img, log_img);	
	log_img *= 1.5;

	normalize(log_img, log_img, 0, 255, NORM_MINMAX); 
	convertScaleAbs(log_img, log_img);

	/* Gamma transformation
		s = c * r ^ g  <- c = 255, g = 0.5  */
	Mat gamma_img = img.clone();
	for (int i = 0; i < gamma_img.rows; ++i)
		for (int j = 0; j < gamma_img.cols; ++j)
			gamma_img.at<uchar>(i, j) = 100, 200;

	
	imshow("input img",img);
	imshow("negative img", negative_img);
	imshow("log_img", log_img);
	imshow("gamma_img", gamma_img);

	waitKey(0);
	return 0;
}

