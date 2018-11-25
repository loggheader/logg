#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "core/filters/basic_filters.hpp"

////////////////////Some basic filters to use anywhere/////////////////////
/*
derivatives:
kernel_size=odd between 0-30
brightness_contrast_gamma:
gamme=0.0-30.0
brightness_contrast_alpha_beeta :
a=1.0-3.0  b=0-100
dft_frequency_gauss_filter:
workingonit

In order to use it: #include "core/filters/basic_filters.hpp"
*/

void derivatives(cv::Mat &in, cv::Mat &out, int kernel_size, int scale, int delta_value)
 {
  cv::Mat grad_x, grad_y;
  cv::Mat abs_grad_x, abs_grad_y;
  int ddepth = CV_16S;
  Sobel(in, grad_x, ddepth, 1, 0, kernel_size, scale, delta_value, cv::BORDER_DEFAULT);
  Sobel(in, grad_y, ddepth, 0, 1, kernel_size, scale, delta_value, cv::BORDER_DEFAULT);
  convertScaleAbs(grad_x, abs_grad_x);
  convertScaleAbs(grad_y, abs_grad_y);
  addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, out);
}


void brightness_contrast_gamma(cv::Mat &in ,cv::Mat &out, double gamma_value)
{
	cv::Mat lookUpTable(1, 256, CV_8U);
  uchar* p = lookUpTable.ptr();
  for( int i = 0; i < 256; ++i)
  {
    p[i] = cv::saturate_cast<uchar>(pow(i / 255.0, gamma_value) * 255.0);
  }
  LUT(in,lookUpTable,out);
}

void brightness_contrast_alpha_beeta(cv::Mat &in ,cv::Mat &out,double alpha_value,int beeta_value)
{
	cv::Mat lookUpTable(1, 256, CV_8U);
	uchar* p = lookUpTable.ptr();
	for( int i = 0; i < 256; ++i)
	{
		p[i] = cv::saturate_cast<uchar>(alpha_value*i+beeta_value);
	}
	LUT(in, lookUpTable, out);
}
