// g++ $(pkg-config --cflags --libs opencv) -std=c++11 watershed.cpp -o watershed

#include <opencv2/core/utility.hpp>
#include "opencv2/opencv.hpp"
#include <cstdio>
#include <iostream>

using namespace cv;
using namespace std;

Mat markerMask, img;
Point prevPt(-1, -1);
static void onMouse(int event, int x, int y, int flags, void*);

int main(){
    Mat img0 = imread("./images/coin_B2.jpg", 1), imgGray;
    if (img0.empty()) {
        cout << "Couldn't open image ";
        return 0;
    }

    resize(img0, img0, Size(500, 500 * (double)img0.rows / (double)img0.cols));
    img0.copyTo(img);
    cvtColor(img, markerMask, COLOR_BGR2GRAY);
    cvtColor(markerMask, imgGray, COLOR_GRAY2BGR);
    markerMask = Scalar::all(0);
    imshow("image", img);
    setMouseCallback("image", onMouse, 0);

    for (;;){
        char c = (char)waitKey(0);

        if (c == 27)
            break;

        if (c == 'r') {
            markerMask = Scalar::all(0);
            img0.copyTo(img);
            imshow("image", img);
        }

        if (c == 'w' || c == ' ') {
            int i, j, compCount = 0;
            vector<vector<Point> > contours;
            vector<Vec4i> hierarchy;

            findContours(markerMask, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

            if (contours.empty())
                continue;
            Mat markers(markerMask.size(), CV_32S);
            markers = Scalar::all(0);
            int idx = 0;
            for (; idx >= 0; idx = hierarchy[idx][0], compCount++)
                drawContours(markers, contours, idx, Scalar::all(compCount + 1), -1, 8, hierarchy, INT_MAX);

            if (compCount == 0)
                continue;
            try {
                imshow("markers", markers * 10000);
            }
            catch (cv::Exception& e) {
                const char* err_msg = e.what();
                std::cout << "exception caught: " << err_msg << std::endl;
            }

            vector<Vec3b> colorTab;
            for (i = 0; i < compCount; i++)
                colorTab.push_back(Vec3b(rand() % 256, rand() % 256, rand() % 256));
            watershed(img0, markers);
            Mat wshed(markers.size(), CV_8UC3);

            // paint the watershed image
            for (i = 0; i < markers.rows; i++)
                for (j = 0; j < markers.cols; j++)
                {
                    int index = markers.at<int>(i, j);
                    if (index == -1)
                        wshed.at<Vec3b>(i, j) = Vec3b(255, 255, 255);
                    else if (index <= 0 || index > compCount)
                        wshed.at<Vec3b>(i, j) = Vec3b(0, 0, 0);
                    else
                        wshed.at<Vec3b>(i, j) = colorTab[index - 1];
                }

            wshed = wshed * 0.7 + imgGray * 0.3;
            imshow("watershed transfom", wshed);
        }
    }
}

static void onMouse(int event, int x, int y, int flags, void*){
    if (x < 0 || x >= img.cols || y < 0 || y >= img.rows)
        return;
    if (event == EVENT_LBUTTONUP || !(flags & EVENT_FLAG_LBUTTON))
        prevPt = Point(-1, -1);
    else if (event == EVENT_LBUTTONDOWN)
        prevPt = Point(x, y);
    else if (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON))
    {
        Point pt(x, y);
        if (prevPt.x < 0)
            prevPt = pt;
        line(markerMask, prevPt, pt, Scalar::all(255), 5, 8, 0);
        line(img, prevPt, pt, Scalar::all(255), 5, 8, 0);
        prevPt = pt;
        imshow("image", img);
    }
}