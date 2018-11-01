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
//MultiWindowTrackBar * MultiWindowTrackBar::global_ptr;


void MultiWindowTrackBar::MultiWindowTrackBar_on_change(int pos, void *data)
{
	((MultiWindowTrackBar *) data)->compute_all_images();
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
	if(ready == false) return;
	for(int i=0;i<compute_next_image.size();i++) compute_next_image[i]( (Mat &) *image[i], (Mat &) *image[i+1], winName[i+1]);
	for(int i=0;i<winName.size();i++) {
		imshow(winName[i],*image[i]);
	}
}




void MultiWindowTrackBar::autowork()
{
	for(int i=0;i<winName.size();i++) {
		namedWindow(winName[i]);
		imshow(winName[i],*image[i]);
	}
	
	//create trackbars and configure them

	ready = false; 
	/*
		for safety reasons, there were issues with the callback function being called
		in the following loop, yielding -1 which were fed to the compute_next_image
		functions leading to segmentation faults :)
	*/

	for(int i=0;i<winName.size();i++){
		trackvalue.push_back(vector<int>());
		for(int j=0;j<trackbarName[i].size();j++){
			trackvalue[i].push_back(0);
			createTrackbar(trackbarName[i][j],winName[i], &trackvalue[i][j], 1, MultiWindowTrackBar_on_change, (void*) this);
			setTrackbarMax(trackbarName[i][j],winName[i],trackbarDimensions[i][j].second);
			setTrackbarMin(trackbarName[i][j],winName[i],trackbarDimensions[i][j].first);
			setTrackbarPos(trackbarName[i][j],winName[i],trackbarDimensions[i][j].first);
		}
	}
	
	/*
		now we are safe and the callback function can be applied normally without fearing 
		a nasty SIGSEGV :)
	*/
	ready = true;
	waitKey(0);
	destroyAllWindows();
}

















