#include "opencv2/opencv.hpp"
#include <iostream> 

using namespace cv;
using namespace std;


int main() {
    CascadeClassifier face_classifier;
    Mat frame, grayframe;
    vector<Rect> faces;
    int i;
    bool near = false;
    bool middle = false;
    bool far = false;
    Mat foreground, result, bgModel, fgModel;

    // loar virtual image
    Mat background = imread("./images/background.jpg", 1);
    // open the webcam
    VideoCapture cap(0);

    // check if we succeeded
    if (background.empty()) {
        cout << "fail load image" << endl;
        return -1;
    }

    if (!cap.isOpened()) {
        cout << "Could not open camera" << endl;
        return -1;
    }

    // copy background img
    Mat temp = background.clone();

    // face detection configuration
    face_classifier.load("./data/haarcascade_frontalface_alt.xml");

   /* HOGDescriptor hog(Size(48, 96), Size(16, 16), Size(8, 8), Size(8, 8), 9);
    hog.setSVMDetector(HOGDescriptor::getDaimlerPeopleDetector());*/
    resize(background, background, Size(200, 200));
    resize(temp, temp, Size(200, 200));

    while (true) {
        // get a new frame from webcam
        cap >> frame;
        resize(frame, frame, Size(200, 200));

        cvtColor(frame, grayframe, COLOR_BGR2GRAY);
        equalizeHist(grayframe, grayframe);
        
        face_classifier.detectMultiScale(
            grayframe, faces, 1.1, 5, 0, Size(10, 10));

        /*hog.detectMultiScale(grayframe, faces, 1.0, Size(4, 4), Size(8, 8), 1.05, 2);
        */
        // reset the background
        background = temp.clone();
 
        // find the rectangle and cut
        for (int i = 0; i < faces.size(); i++) {
            Point lb(faces[i].x+ faces[i].width, faces[i].y+15 + faces[i].height);
            Point tr(faces[i].x, faces[i].y-15);
            Rect rectangle(tr, lb);
            grabCut(frame, result, rectangle, bgModel, fgModel, 2, GC_INIT_WITH_RECT);
            compare(result, GC_PR_FGD, result, CMP_EQ);
            frame.copyTo(background, result);
        }

        /*for (int i = 0; i < faces.size(); i++) {
            Point lb(faces[i].x + faces[i].width, faces[i].y + faces[i].height+15);
            Point tr(faces[i].x, faces[i].y-15);
            rectangle(frame, lb, tr, Scalar(0, 255, 0), 2, 4, 0);
        }*/

       // print the output
        imshow("Project3", background);
        if (waitKey(33) == 27) break;
    }
}