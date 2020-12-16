#include "opencv2/opencv.hpp"
#include <iostream> 

using namespace cv;
using namespace std;

int main() {
    Mat lena, moon, saltnpepper;
    Mat lena_blurred;
    Mat lena_left, lena_right, lena_filtered_left, lena_filtered_right;
    Mat moon_lap, moon_sharp, moon_left, moon_right, moon_filtered_left, moon_filtered_right;
    Mat lena_filtered, moon_filtered, saltnpepper_filtered;

    lena = imread("./images/lena.png", 0);
    moon = imread("./images/moon.png", 0);
    saltnpepper = imread("./images/saltnpepper.png", 0);

    if (lena.empty() || moon.empty() || saltnpepper.empty())
        return 0;

    // #1. Perform Average filtering on the left-half of the image
    blur(lena, lena_blurred, Size(7, 7));

    lena_left = lena_blurred(Rect(0, 0, lena_blurred.cols/2, lena_blurred.rows));
    lena_right = lena(Rect(lena.cols / 2, 0, lena.cols / 2, lena.rows));
    lena_filtered = Mat::zeros(lena.size(), lena.type());
    lena_filtered_left = lena_filtered(Rect(0, 0, lena_filtered.cols / 2, lena_filtered.rows));
    lena_filtered_right = lena_filtered(Rect(lena_filtered.cols / 2, 0, lena_filtered.cols / 2, lena_filtered.rows));

    add(lena_left, lena_filtered_left, lena_filtered_left);
    add(lena_right, lena_filtered_right, lena_filtered_right);


    // #2. Perform sharpening on the right-half of the image
    Laplacian(moon, moon_lap, CV_16S);
    convertScaleAbs(moon_lap, moon_lap);
    add(moon_lap, moon, moon_sharp);

    moon_filtered = Mat::zeros(moon.size(), moon.type());
    moon_filtered_left = moon_filtered(Rect(0, 0, moon_filtered.cols/2, moon_filtered.rows));
    moon_filtered_right = moon_filtered(Rect(moon_filtered.cols/2, 0, moon_filtered.cols/2, moon_filtered.rows));
    moon_left = moon(Rect(0, 0, moon.cols / 2, moon.rows));
    moon_right = moon_sharp(Rect(moon_sharp.cols/2, 0, moon_sharp.cols/2, moon_sharp.rows));

    add(moon_left, moon_filtered_left, moon_filtered_left);
    add(moon_right, moon_filtered_right, moon_filtered_right);


    // #3. Perform median filtering on the image
    medianBlur(saltnpepper, saltnpepper_filtered, 9);


    // Show images
    imshow("lena", lena);
    imshow("lena_filtered", lena_filtered);
    imshow("moon", moon);
    imshow("moon_filter", moon_filtered);
    imshow("saltnpepper", saltnpepper);
    imshow("saltnpepper_filtered", saltnpepper_filtered);

    waitKey(0);
}