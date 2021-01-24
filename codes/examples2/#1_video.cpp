#include "opencv2/opencv.hpp"
#include <iostream> 

using namespace cv;
using namespace std;

int main(){
    Mat frame;
	VideoCapture cap("./images/background-2.mp4");
	double fps = cap.get(CAP_PROP_FPS);
	int delay = 1000 / fps;

	if (!cap.isOpened()){
		cerr << "file open fail" << endl;
		exit(-1);
	}
	while (1) {
			cap >> frame;
			double cur_frame = cap.get(CAP_PROP_POS_FRAMES);
			double total_frames = cap.get(CAP_PROP_FRAME_COUNT);
	
			if (frame.empty()) {
				cerr << "empty frame" << endl;
				break;
			}

			waitKey(delay);

			cout << "frames: " << cur_frame << " / " << total_frames << endl;

			imshow("vid", frame);

			if (cur_frame == cvRound(3 * fps)) {
				waitKey(0);
				break;
			}
	}
	destroyAllWindows();
	return 0;
}