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
    // open the webcam
    VideoCapture cap("./images/Faces.mp4");

    // check if we succeeded
    if (!cap.isOpened()) {
        cout << "Could not open camera" << endl;
        return -1;
    }

    // face detection configuration
    face_classifier.load("./data/haarcascade_frontalface_alt.xml");
    char initial = 'x';

    while (true) {
        // get a new frame from webcam
        cap >> frame;
        resize(frame, frame, Size(500, 400));

        cvtColor(frame, grayframe, COLOR_BGR2GRAY);
        
        char key = waitKey(33);
        if (key != 'n' && key != 'f' && key != 'm') {
            // 이전 key 값 기억
            if (near == true) key = 'n';
            else if (far == true) key = 'f';
            else if (middle == true) key = 'm';
        }

        switch (key) {
        case 'n': 
            cout << "This is n" << endl;
            face_classifier.detectMultiScale(
                grayframe, faces, 1.2, 3, 0, Size(30, 30), Size(50, 50)
            );
            near = true;
            far = false;
            middle = false;
            break;
         
        case 'f':
            cout << "This is f" << endl;
            face_classifier.detectMultiScale(
                grayframe, faces, 1.2, 2.5, 0, Size(1, 1), Size(15, 15)
            );
            far = true;
            near = false;
            middle = false;
            break;
        case 'm':
            cout << "This is m" << endl;
            face_classifier.detectMultiScale(
                grayframe, faces, 1.2, 2.5, 0, Size(22, 22), Size(26, 26)
            );
            middle = true;
            near = false;
            far = false;
            break;
        default:
            cout << "This is default" << endl;
            break;
        }

        // draw the results
        for (int i = 0; i < faces.size(); i++) {
            Point lb(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
            Point tr(faces[i].x, faces[i].y);
            rectangle(frame, lb, tr, Scalar(0, 255, 0), 2, 4, 0);
        }
        // print the output
        imshow("Faces", frame);
        if (waitKey(33) == 27) break;
    }
}