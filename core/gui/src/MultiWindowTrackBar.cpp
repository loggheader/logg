#include "core/gui/MultiWindowTrackBar.hpp"
#include <opencv2/highgui.hpp>
#include <string>
#include <iostream>
using namespace std;
using namespace cv;

/*
	WARNING: CURRENTLY NO CHECKING FOR WINDOW NAME DUPLICATES AND SO ON
	THIS CODE IS ONLY FOR EXPERIMENTING AND TESTING PURPOSES!
*/
MultiWindowTrackBar * MultiWindowTrackBar::global_ptr;


void MultiWindowTrackBar::MultiWindowTrackBar_on_change(int, void *)
{
	(MultiWindowTrackBar::global_ptr)->compute_all_images();
}

MultiWindowTrackBar::MultiWindowTrackBar(cv::Mat & original_image, std::string origin_name)
{
	image.push_back(&original_image);
	winName.push_back(origin_name);
	trackbarName.push_back(vector<string>());
	trackbarDimensions.push_back(vector<pair<int,int> >());
}


void MultiWindowTrackBar::add_window(cv::Mat& _image, const string & _winName, NextImage _compute_next_image)
{
	winName.push_back(_winName);
	image.push_back(&_image);
	trackbarName.push_back(vector<string>());
	trackbarDimensions.push_back(vector<pair<int,int> >());
	compute_next_image.push_back(_compute_next_image);
}


void MultiWindowTrackBar::add_trackbar_on_window(const string &_winName, const string &_trackbar, int min_track_val, int max_track_val)
{
	for(int i=1;i<winName.size();i++){
		if(winName[i] == _winName){
			trackbarName[i].push_back(_trackbar);
			trackbarDimensions[i].push_back(make_pair(min_track_val,max_track_val));
		}
	}
}


void MultiWindowTrackBar::compute_all_images()
{
	for(int i=0;i<compute_next_image.size();i++) compute_next_image[i]( (Mat &) *image[i], (Mat &) *image[i+1], winName[i+1]);
	for(int i=0;i<winName.size();i++) {
		imshow(winName[i],*image[i]);
	}
}




void MultiWindowTrackBar::autowork()
{
	MultiWindowTrackBar * stack_ptr = MultiWindowTrackBar::global_ptr;
	MultiWindowTrackBar::global_ptr = this;
	for(int i=0;i<winName.size();i++) {
		namedWindow(winName[i]);
	}

	//create trackbars and configure them
	for(int i=0;i<winName.size();i++){
		trackvalue.push_back(vector<int>());
		for(int j=0;j<trackbarName[i].size();j++){
			trackvalue[i].push_back(0);
			createTrackbar(trackbarName[i][j],winName[i], &trackvalue[i][j], 1, MultiWindowTrackBar_on_change);
			setTrackbarMax(trackbarName[i][j],winName[i],trackbarDimensions[i][j].second);
			setTrackbarMin(trackbarName[i][j],winName[i],trackbarDimensions[i][j].first);
			setTrackbarPos(trackbarName[i][j],winName[i],trackbarDimensions[i][j].first);
		}
	}
	for(int i=0;i<winName.size();i++) {
		imshow(winName[i],*image[i]);
	}

	waitKey(0);
	destroyAllWindows();
	MultiWindowTrackBar::global_ptr = stack_ptr;
}

















