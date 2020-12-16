// g++ $(pkg-config --cflags --libs opencv) -std=c++11 10-1.coin_count1.cpp -o 10-1.coin_count1
#include "opencv2/opencv.hpp"
#include <iostream> 

using namespace cv;
using namespace std;

int main(){
	Mat image = imread("./images/coin_A2.jpg");
	Mat gray;

	float width = 500;
	float height = width * ((double)image.rows / (double)image.cols);

	resize(image, image, Size(width, height));
	imshow("src", image);

	//	cvtColor(image, gray, CV_BGR2GRAY);
	cvtColor(image, gray, COLOR_BGR2GRAY);
	//GaussianBlur(gray, gray, Size(3, 3), 1.5, 1.5);
	GaussianBlur(gray, gray, Size(7, 7), 1.5, 1.5);

	std::vector<Vec3f> coin;
	// A vector data type to store the details of coins.

	imshow("gray", gray);
	Canny(gray, gray, 180, 120, 3);
	imshow("canny", gray);
	//HoughCircles(gray, coin, HOUGH_GRADIENT, 2, 30, 120, 120, 30, 150);
	//HoughCircles(gray, coin, HOUGH_GRADIENT, 2, 30, 180, 120, 30, 100); // best option
	HoughCircles(gray, coin, HOUGH_GRADIENT, 5, 80, 180, 120, 30, 100); // best option
	// Argument 1: Input image mode
	// Argument 2: A vector that stores 3 values: x,y and r for each circle.
	// Argument 3: CV_HOUGH_GRADIENT: Detection method.
	// Argument 4: The inverse ratio of resolution.
	// Argument 5: Minimum distance between centers.
	// Argument 6: Upper threshold for Canny edge detector.
	// Argument 7: Threshold for center detection.
	// Argument 8: Minimum radius to be detected. Put zero as default
	// Argument 9: Maximum radius to be detected. Put zero as default
	int L = coin.size();
	// Get the number of coins.

	std::cout << "\n The number of coins is: " << L << "\n\n";

	// To draw the detected circles.
	for (size_t i = 0; i < coin.size(); i++){
		Point center(cvRound(coin[i][0]), cvRound(coin[i][1]));
		// Detect center
		// cvRound: Rounds floating point number to nearest integer.
		int radius = cvRound(coin[i][2]); // To get the radius from the second argument of vector coin.
		circle(image, center, 4, Scalar(0, 255, 0), -1, 8, 0);
		// circle center

		//  To get the circle outline.     
		circle(image, center, radius, Scalar(0, 0, 255), 3, 8, 0); // circle outline
		std::cout << " Center location for circle " << i + 1 << " :"
			<< center << "\n Diameter : " << 2 * radius << "\n";
	}
	std::cout << "\n";
	imshow("res", image);
	waitKey(0);
	return L;
}