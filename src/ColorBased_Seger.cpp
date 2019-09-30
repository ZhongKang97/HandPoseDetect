#include"../include/ColorBased_Seger.h"

ColorBased_Seger::~ColorBased_Seger()
{
}
cv::Rect ColorBased_Seger::runSegment(cv::Mat frame)
{
	cv::Mat dstImg;
	cv::Mat showImg = cv::Mat::zeros(frame.rows, frame.cols, CV_8UC3);
	cv::inRange(frame, target_color - low_treash, target_color + high_treash, dstImg);
	cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(15, 15));
	cv::dilate(dstImg, dstImg, element);
	cv::imshow("binary Image", dstImg);
	vector<vector<cv::Point>> contours;
	vector<cv::Vec4i> hierarchy;
	cv::findContours(dstImg, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);
	int index = 0;	
	double maxAera = 0;
	int max_id = 0;
	if (contours.size() >= 1)
	{
		for (; index >= 0; index = hierarchy[index][0])
		{
			cv::Scalar color(rand() & 255, rand() & 255, rand() & 255);
			cv::drawContours(showImg, contours, index, color, cv::FILLED, 8, hierarchy);
			double t_area = contourArea(contours[index]);
			if ( t_area >= maxAera)
			{
				maxAera = t_area;
				max_id = index;
			}
		}
		cv::imshow("Contours", showImg);
		cv::waitKey(10);
		return boundingRect(contours[max_id]);
	}
	else return cv::Rect(-1, -1, 0, 0);
}
