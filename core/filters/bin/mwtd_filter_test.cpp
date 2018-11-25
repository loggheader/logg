#include <opencv2/opencv.hpp>
#include "core/gui/MultiWindowTrackBar.hpp"
#include "core/filters/basic_filters.hpp"
#include <iostream>
#include <cstdio>
#include <cstdlib>

void help()
{
  std::cout<<"Usage: ./mwtb_filter_test <image_name>"<<std::endl;
  exit(1);
}

void to_gray(cv::Mat & _color, cv::Mat & _gray)
{
	cvtColor(_color,_gray,cv::COLOR_BGR2GRAY);
}

void canny_filter (cv::Mat &in, cv::Mat &out, const std::string &window)
{
	int low = cv::getTrackbarPos("lower",window);
	int upper = cv::getTrackbarPos("upper",window);
	int kernel_size = cv::getTrackbarPos("kernel_size",window);
  if(kernel_size%2 == 0) kernel_size++;
  Canny(in, out, low, upper,kernel_size);
}

void blur_filter(cv::Mat &in, cv::Mat &out, const std::string &window)
{
	int kernel_size = cv::getTrackbarPos("kernel_size",window);
  if(kernel_size %2 == 0) kernel_size++;
  if(kernel_size<0) kernel_size = 3;
	blur(in,out,cv::Size(kernel_size,kernel_size));
}

void derivatives_filter(cv::Mat &in ,cv::Mat &out, const std::string &window)
{
  int kernel_size= 1+2*cv::getTrackbarPos("kernel_size",window);
	int scale=cv::getTrackbarPos("scale",window);
	int delta=cv::getTrackbarPos("delta",window);
	derivatives(in,out,kernel_size,scale,delta);
}

void brightness_contrast_filter(cv::Mat &in ,cv::Mat &out, const std::string &window) //alpha-beeta way
{
	double alpha_value=(double)cv::getTrackbarPos("alpha",window)/100;
	int beeta_value=cv::getTrackbarPos("beeta",window)/100;
	brightness_contrast_alpha_beeta(in,out,alpha_value,beeta_value);
}

void brightness_correction_filter(cv::Mat &in ,cv::Mat &out, const std::string &window)//gamma way
{
  double gamma_value=(double)cv::getTrackbarPos("gamma",window)*0.03-0.03;
  brightness_contrast_gamma(in,out,gamma_value);
}


int main(int argc, char **argv)
{
	cv::Mat img = cv::imread(argv[1]);
	if(img.empty()) img=cv::imread("/home/piyi/loggheader/learning_opencv/t1.jpg");

  to_gray(img,img);

  cv::Mat blur_out=img.clone();
  cv::Mat brightness_correction_out=img.clone();
  cv::Mat brightness_contrast_out=img.clone();
  cv::Mat derivatives_out=img.clone();
  cv::Mat canny_out=img.clone();

  MultiWindowTrackBar mwtb(img);

  mwtb.add_window(blur_out,"blur_out",blur_filter);
	mwtb.add_trackbar_on_window("blur_out","kernel_size",1,1000);

	mwtb.add_window(brightness_correction_out,"brightness_correction_out",brightness_correction_filter);
	mwtb.add_trackbar_on_window("brightness_correction_out","gamma",1,1000);

	mwtb.add_window(brightness_contrast_out,"brightness_contrast_out",brightness_contrast_filter);
	mwtb.add_trackbar_on_window("brightness_contrast_out","alpha",1,300);
  mwtb.add_trackbar_on_window("brightness_contrast_out","beeta",1,1000);

  mwtb.add_window(derivatives_out,"derivatives_out",derivatives_filter);
	mwtb.add_trackbar_on_window("derivatives_out","kernel_size",0,14);
	mwtb.add_trackbar_on_window("derivatives_out","scale",1,1000);
	mwtb.add_trackbar_on_window("derivatives_out","delta",1,1000);

	mwtb.add_window(canny_out,"canny_out",canny_filter);
	mwtb.add_trackbar_on_window("canny_out","kernel_size",3,7);
	mwtb.add_trackbar_on_window("canny_out","upper",1,1000);
	mwtb.add_trackbar_on_window("canny_out","lower",1,1000);

	mwtb.autowork();
}
