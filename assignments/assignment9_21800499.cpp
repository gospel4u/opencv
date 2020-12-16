#include "opencv2/opencv.hpp"
#include <iostream> 

using namespace cv;
using namespace std;

int main() {
    Mat finger, adaptive, adaptive1;
    finger = imread("./images/finger_print.png", 0);
    adaptive1 = imread("./images/adaptive_1.jpg", 0);
    adaptive = imread("./images/adaptive.png", 0);

    if (finger.empty() || adaptive1.empty() || adaptive.empty()) {
        cout << "empty frame" << endl;
        return -1;
    }

    threshold(finger, finger, 0, 255, THRESH_BINARY | THRESH_OTSU);
    adaptiveThreshold(adaptive1, adaptive1, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 105, 15);
    adaptiveThreshold(adaptive, adaptive, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 5, 10);

    imshow("finger_print", finger);
    imshow("adaptive_1", adaptive1);
    imshow("adaptive", adaptive);

    waitKey(0);
    return 0;
}