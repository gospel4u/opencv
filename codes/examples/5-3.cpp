#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat img, res;
    vector<Mat> channels; 

    img = imread("images/Fig06_chalk.tif", 1);
    resize(img, img, Size(0, 0), 0.5, 0.5);
    uchar gamma_table[256]; 
    for (int i = 0; i < 256; i++) {
        gamma_table[i] = pow((i / 255.f), 2.5) * 255.0f;
    }

    Mat gamma_mat(1, 256, CV_8UC1, gamma_table);
    split(img, channels);

    for (int i = 0; i < 3; i++) {
        LUT(channels[i], gamma_mat, channels[i]); 
    }
    merge(channels, res);

    imshow("Original img", img); 
    imshow("Result img", res); 
    waitKey(0);
}



   