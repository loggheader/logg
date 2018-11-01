#include <opencv2/opencv.hpp>
#include "core/gui/MultiWindowTrackBar.hpp"
#include <iostream>
#include <cstdio>
#include <cstdlib>


using namespace std;
using namespace cv;



void help()
{
	fprintf(stderr,"Usage:\n./mwtbtest [image name]\n");
	exit(1);
}

void to_gray(Mat & _color, Mat & _gray, const string &window)
{
	//Mat & color = *_color;
	//Mat & gray  = *_gray;
	cvtColor(_color,_gray,COLOR_BGR2GRAY);
}



void canny_filter (Mat &blurred, Mat &canny_out, const string &window)
{
	cout<<window<<endl;
	int low = getTrackbarPos("lower",window);
	int upper = getTrackbarPos("upper",window);
	int k = getTrackbarPos("kernel_size",window); 
	cout<<"canny "<<k<<" "<<low<<" "<<upper<<" ";
	if(k%2 == 0) k++;
	cout<<getTrackbarPos("lower",window)<<" "<<getTrackbarPos("lower",window)<<endl;
	Canny(blurred, canny_out, low, upper,k);
}


void blur_filter(Mat &img, Mat &blurred, const string &window)
{
	int k = getTrackbarPos("kernel_size",window);
	cout<<"blur called "<<k<<endl; if(k %2 == 0) k++; if(k<0) k = 3;
	cvtColor(img,blurred,COLOR_BGR2GRAY);
	cout<<k<<endl;
	blur(blurred,blurred,Size(k,k));
}

int main(int argc, char **argv)
{
	Mat img = imread(argv[1]);
	if(img.empty()) help();
	Mat blurred = img.clone(); //cvtColor(img,gray, COLOR_BGR2GRAY);
	Mat canny_out = img.clone();
	MultiWindowTrackBar mwtb(img);
	mwtb.add_window(blurred,"b",blur_filter);
	mwtb.add_trackbar_on_window("b","kernel_size",3,7);
	mwtb.add_window(canny_out,"canny_out",canny_filter);
	mwtb.add_trackbar_on_window("canny_out","kernel_size",3,7);
	mwtb.add_trackbar_on_window("canny_out","upper",40,400);
	mwtb.add_trackbar_on_window("canny_out","lower",40,400);
	mwtb.autowork();
}


