#include "../include/ColorBased_Seger.h"
#include<Python.h>
#include<iostream>
#include<string>
#include<boost/asio.hpp>
#include<boost/bind.hpp>
using namespace std;
using namespace boost::asio;
int g_targetColor_B = 186;
int g_targetColor_G = 136;
int g_targetColor_R = 88;
bool custom_color = false;
cv::Mat frame;
void on_mouse(int event, int x, int y, int, void *);

int main(int argc, char **argv)
{
	ColorBased_Seger Seger;
	cv::namedWindow("frame");
	cv::createTrackbar("TargetColor_B", "frame", &g_targetColor_B, 255);
	cv::createTrackbar("TargetColor_G", "frame", &g_targetColor_G, 255);
	cv::createTrackbar("TargetColor_R", "frame", &g_targetColor_R, 255);
	cv::setMouseCallback("frame", on_mouse);
	Seger.setLowTreash(cv::Scalar(20, 20, 20));
	Seger.setHighTreash(cv::Scalar(20, 20, 20));
	io_service iosev;
    serial_port sp(iosev,"/dev/ttyUSB0");
    sp.set_option(serial_port::baud_rate(9600));
    sp.set_option(serial_port::flow_control(serial_port::flow_control::none));
    sp.set_option(serial_port::parity(serial_port::parity::none));
    sp.set_option(serial_port::stop_bits(serial_port::stop_bits::one));
    sp.set_option(serial_port::character_size(8));
    
	Py_Initialize();
    const char * cstr_cmd = "sys.path.append('/home/pi/CODEing/HandPoseDetect/src')";
    PyRun_SimpleString("import sys");
    PyRun_SimpleString(cstr_cmd);
    //python 2.7 和 python 3.5是有区别的。
    //python 3.5需要用wchar_t
    PyObject * p_Moudle,* p_Func;
    PyObject *p_Value;
    p_Moudle = PyImport_ImportModule("get_Distance_TFmini_Plus");
	if(p_Moudle == NULL) cout<<"p_Moudle import failed"<<endl;
	else 
    {
        p_Func = PyObject_GetAttrString(p_Moudle,"getTFminiData");
        if(p_Func == NULL) cout<<"p_Func import failed"<<endl;
	}
	cv::VideoCapture cap(0);
	if (cap.isOpened())
	{
		bool initColor = true;
		double maxArea = 0;
		cv::Scalar bestTargetColor;
		while (true)
		{
			int distance=0;
			char buf[1];
			read(sp,buffer(buf));
			cout<<"recevied : "<<buf[0]<<endl;
			cap >> frame;
			if (frame.empty())
				break;
			if( buf[0]== 'B' )
			{
			Seger.setTargetColor(cv::Scalar(g_targetColor_B, g_targetColor_G, g_targetColor_R));
			cv::Rect object = Seger.runSegment(frame);
			if (object.x > 0)
			{
				if (initColor)
				{
					
					initColor = false;
					maxArea = object.area();
					cv::Mat roi = frame(cv::Rect(object.x, object.y, 6, 6));
					cv::Scalar target = cv::mean(roi);
					bestTargetColor = cv::Scalar(target[0], target[1], target[2]);
					Seger.setTargetColor(bestTargetColor);
					cout << "initColor: " << target << endl;
				}
				else
				{
					if (object.area() > maxArea)
					{
						maxArea = object.area();
						cv::Mat roi = frame(object);
						cv::Scalar target = mean(roi);
						bestTargetColor = cv::Scalar(target[0], target[1], target[2]);
						Seger.setTargetColor(bestTargetColor);
						cout << "best target color is :" << bestTargetColor << endl;
						cout << "maxArea is " << maxArea << endl;
					}
				}
				p_Value = PyObject_CallObject(p_Func,NULL);
                int res= PyInt_AsLong(p_Value);
				if(res != -1) distance = res;
				rectangle(frame, object, cv::Scalar(0, 0, 255));
				circle(frame, cv::Point(object.x + object.width / 2.0, object.y + object.height / 2.0), 5, cv::Scalar(0, 0, 255), cv::FILLED);
				int font_face = cv::FONT_HERSHEY_COMPLEX; 
				double font_scale = 1;					  
				int thickness = 2;						  
				std::string text_d_x = cv::format("HandPose_X: %f ", object.x + object.width / 2.0);
				std::string text_d_y = cv::format("HandPose_Y: %f ", object.y + object.height / 2.0);
				putText(frame, text_d_x, cv::Point(0, 30), font_face, font_scale, cv::Scalar(255, 0, 135), thickness, 8, 0);
				putText(frame, text_d_y, cv::Point(0, 60), font_face, font_scale, cv::Scalar(255, 0, 135), thickness, 8, 0);
				string testData = cv::format("%-8.2f%-8.2f%-8.2f", object.x + object.width / 2.0, object.y + object.height / 2.0, distance);
				//string testData = cv::format("%-8.2f%-8.2f%-8.2f", 2260.0, 0.0, -1900.0);
				write(sp,buffer(testData.data(),testData.size()));
				std::cout << testData << endl;
			}
			imshow("frame", frame);
			char key = cv::waitKey(10);
			if (key == 27)
				break;
			}
		}
	}
	iosev.run();
}
void on_mouse(int event, int x, int y, int, void *)
{
	if (event == CV_EVENT_LBUTTONDOWN && custom_color)
	{
		cv::Vec3b value;
		value = frame.at<cv::Vec3b>(y, x);
		g_targetColor_B = value[0];
		g_targetColor_G = value[1];
		g_targetColor_R = value[2];
		cout << "now the color is (BRG): " << g_targetColor_B << " " << g_targetColor_G << " " << g_targetColor_R << endl;
	}
}
