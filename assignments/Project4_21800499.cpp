#include "opencv2/opencv.hpp"
#include <iostream> 

using namespace cv;
using namespace std;

struct Stack {
	Mat img;
	vector<Point2f> in, out;
};
using stack = Stack *;

#if 0
static; void onMouse(int event, int x, int y, int, void* param) {
	stack mp = (stack)param; 
	Mat img = mp->img; 
	if (event == EVENT_LBUTTONDOWN) // left button
	{
		Mat result;
		//InsertpositionfromLT.Directionisclock-wise
		mp->in.push_back(Point2f(x, y));
		cout << "x: " << x << ", y: " << y << endl;
		if (mp->in.size() == 4)
		{
			//Compute Homographyfrom 4 matching pairs
			Mat homo_mat= getPerspectiveTransform(mp->in, mp->out);
			//Image warping
			warpPerspective(img, result, homo_mat, Size(200, 200));
			imshow("output", result);
		}
		else
		{
			result = img.clone();
			for (size_t i= 0; i< mp->in.size(); i++)
			{
				circle(result, mp->in[i], 3, Scalar(0, 0, 255), 5);
			}
			imshow("input", result);
		}
	}
	//Resetpositions
	if (event == EVENT_RBUTTONDOWN)
	{
		mp->in.clear();
		imshow("input", img);
	}
}
#else
void getPoints(Mat input, void * param) {
	stack gp = (stack)param;
	Mat img = gp->img;
	Mat temp;
	Mat result;
	
	cvtColor(input, temp, COLOR_BGR2GRAY);
	blur(temp, temp, Size(5, 5));
	threshold(temp, temp, 100, 255, THRESH_BINARY);
	Canny(temp, temp, 10, 60, 3);

	// Find Contours
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(temp, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	// Find largest bound
	int largest_area = 0;
	int largest_index = 0;
	for (int i = 0; i < contours.size(); i++) {
		if (boundingRect(Mat(contours[i])).area() > largest_area) {
			largest_area = boundingRect(Mat(contours[i])).area();
			largest_index = i;
		}
	}
	
	/*cvtColor(temp, temp, COLOR_GRAY2BGR);
	drawContours(temp, contours, largest_index, Scalar(255, 255, 0), 2);
	imshow("temp", temp);*/

	int x1=0, x2=0, x3=0, x4=0;
	int y1=0, y2=0, y3=0, y4=0;
	int max = 0;
	int min = 10000;
	int max2 = -10000;
	int min2 = 10000;
	for (int i = 0; i < contours[largest_index].size(); i++) {
		int curr_x = contours[largest_index][i].x;
		int curr_y = contours[largest_index][i].y;
		// Find (x1,y1) -> min(x+y)
		if ((curr_x + curr_y) < min) {
			min = curr_x + curr_y;
			x1 = curr_x;
			y1 = curr_y;
		}

		// Find (x2, y2) -> min(y-x)
		if ((curr_y - curr_x) < min2) {
			min2 = curr_y - curr_x;
			x2 = curr_x;
			y2 = curr_y;
		}

		// Find (x3, y3) -> max(x+y)
		if ((curr_x + curr_y) > max) {
			max = curr_x + curr_y;
			x3 = curr_x;
			y3 = curr_y;
		}

		// Find (x4, y4) -> max(y-x)
		if ((curr_y - curr_x) > max2) {
			max2 = curr_y - curr_x;
			x4 = curr_x;
			y4 = curr_y;
		}
	}
		
	cout << "(x1, y1): " << x1 << ", " << y1 << endl;
	cout << "(x2, y2): " << x2 << ", " << y2 << endl;
	cout << "(x3, y3): " << x3 << ", " << y3 << endl;
	cout << "(x4, y4): " << x4 << ", " << y4 << endl;

	gp->in.push_back(Point2f(x1, y1));
	gp->in.push_back(Point2f(x2, y2));
	gp->in.push_back(Point2f(x3, y3));
	gp->in.push_back(Point2f(x4, y4));
	
	/*gp->in.push_back(Point2f(85, 100));
	gp->in.push_back(Point2f(325, 100));
	gp->in.push_back(Point2f(360, 285));
	gp->in.push_back(Point2f(70, 300));*/
	Mat homo_mat = getPerspectiveTransform(gp->in, gp->out);
	warpPerspective(img, result, homo_mat, Size(200, 200));
	imshow("output", result);
}

#endif
int main() { 
	Mat input = imread("./images/namecard.jpg"); 
	resize(input, input, Size(400, 400));
	imshow("input", input); 

	Stack mp;
	mp.out.push_back(Point2f(0, 0)); 
	mp.out.push_back(Point2f(200, 0)); 
	mp.out.push_back(Point2f(200, 200)); 
	mp.out.push_back(Point2f(0, 200));
	mp.img = input; 
	
	getPoints(input, (void*)&mp);
	//setMouseCallback("input", onMouse, (void*)&mp); 
	waitKey(); 
	return 0; 
}