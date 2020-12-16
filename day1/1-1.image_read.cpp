// g++ $(pkg-config --cflags --libs opencv) -std=c++11 image_read.cpp -o image_read
#include "opencv2/opencv.hpp"
#include <iostream> 

using namespace cv;
using namespace std;

int main(){
    Mat gray_image;
    Mat color_image;
    gray_image = imread("./images/lena.png", 0 );
    color_image = imread("./images/lena.png");
    if (gray_image.empty() || color_image.empty()) {
        cout << "file read error" << endl;
        exit(-1);
    }

    Mat roi(color_image, Rect(0, 0, 300, 300));
    Mat roi2_t(color_image, Rect(100, 0, 400, 300));
    roi /= 2;
    Mat roi2 = roi2_t.clone();

    vector<Mat> ch;
    split(roi2, ch);
    ch[2] = 0;
    merge(ch, roi2);

    Mat gray_color;
    cvtColor(gray_image, gray_color, COLOR_GRAY2BGR);

    line(gray_color, Point(0, 0), Point(100, 400), Scalar(255, 255, 0), 3);
    rectangle(gray_color, Point(100, 100), Point(300, 300), Scalar(255, 0, 255), -1);
    putText(gray_color, "this is a text", Point(100, 100), FONT_HERSHEY_PLAIN, 1.0, Scalar(0, 255, 255), 2);


    resize(roi2, roi2, Size(500, 500));

    imshow("roi", roi);
    imshow("roi2", roi2);

    imshow("gray image", gray_image);
    imshow("color image", color_image);
    imshow("gray_col", gray_color);

    
    waitKey(0);
    destroyAllWindows();
}
