// g++ $(pkg-config --cflags --libs opencv) -std=c++11 video_read.cpp -o video_read
#include "opencv2/opencv.hpp"
#include <iostream> 

using namespace cv;
using namespace std;

int main(){
    Mat frame;
	VideoCapture cap("./images/background-2.mp4");

	if (!cap.isOpened()){
		cerr << "file open fail" << endl;
		exit(-1);
	}
	for(int i = 0; i < 3 * cap.get(CAP_PROP_FPS); i++) {
		cap >> frame;
		if (frame.empty()){
			cerr << "empty frame" << endl;
			break;
		}
		imshow("vid", frame);
		
		cout << "frame " << cap.get(CAP_PROP_POS_FRAMES) << " / " << cap.get(CAP_PROP_FRAME_COUNT) <<"\n";
		waitKey(33);
		
	}
	destroyAllWindows();
}
  