#include<opencv2/opencv.hpp>
#include<opencv2/opencv_modules.hpp>
#include<iostream>
using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	VideoCapture cap(1);
	if (cap.isOpened())
	{
		Mat frame;
		int counter_v = 0;
		int counter_t = 0;
		while (true)
		{
			cap >> frame;
			if (frame.empty()) break;
			imshow("frame", frame);
			char key = waitKey(1);
			if (key == 27) break;
			if (key == 'p')
			{
				char key_2 = waitKey(0);
				if (key_2 == 'v')
				{
					string filename = cv::format("D:/CODEing/ComputerVision_codeSources/EBoardPoseDetec/data/%d.png", counter_v++);
					imwrite(filename, frame);
					cout << "now recording the sample to :" << filename << endl;
				}
				else if(key_2 == 't')
				{
					string filename = cv::format("D:/CODEing/Python_codeSources/HandPoseDetect/data/Test/%d.png", counter_t++);
					//imwrite(filename, frame);
					cout << "now recording the sample to :" << filename << endl;
				}
			}
		}
	}
}