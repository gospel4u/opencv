#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void get_color_table(uchar tables[], int amt);

int main() {
    Mat hsv, blurr, enhanced; 
    Mat img = imread("images/Fig06_strawberry.tif", 1);
    resize(img, img, Size(0, 0), 0.5, 0.5);
    imshow("org", img);

    cvtColor(img, hsv, COLOR_BGR2HSV); 

    std::vector<Mat> channels(3);
    split(hsv, channels);
    imshow("before V", channels[2]);

    unsigned char color_comp_tab[256]; 
    get_color_table(color_comp_tab, 90);
    Mat mapping(1, 256, CV_8UC1, color_comp_tab); 
    LUT(channels[0], mapping, channels[0]); // H 
    channels[2] = 255 - channels[2]; // V

    imshow("after V", channels[2]);
    merge(channels, hsv); 
    cvtColor(hsv, img, COLOR_HSV2BGR); 
    imshow("inverse", img);

    waitKey(0);
}

void get_color_table(uchar tables[], int amt) {
	for (int i = 0; i <= 180; i++) {
        tables[i] = (i + amt) % 180;
    }
		
	for (int i = 181; i < 256; i++) {
        tables[i] = 0;
    }
}



   