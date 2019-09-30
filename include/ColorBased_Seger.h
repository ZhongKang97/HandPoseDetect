#pragma once
#ifndef _COLORBASED_SEGER_H
#define _COLORBASED_SEGER_H
#include<opencv2/opencv.hpp>
#include<opencv2/opencv_modules.hpp>
#include<iostream>
using namespace std;
class ColorBased_Seger
{
public:
	ColorBased_Seger(cv::Scalar target = cv::Scalar(0, 0, 0), cv::Scalar low = cv::Scalar(10,10,10), cv::Scalar high = cv::Scalar(10,10,10)):target_color(target)
	{
		this->low_treash = low;
		this->high_treash = high;
	}
	~ColorBased_Seger();
	cv::Rect runSegment(cv::Mat frame);
	void setTargetColor(cv::Scalar value)
	{
		this->target_color = value;
	}
	void setLowTreash(cv::Scalar low)
	{
		this->low_treash = low;
	}
	void setHighTreash(cv::Scalar high)
	{
		this->high_treash = high;
	}
private:
	cv::Scalar target_color;
	cv::Scalar low_treash;
	cv::Scalar high_treash;
};



#endif // !_COLORBASED_SEGER_H
