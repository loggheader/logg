#include "core/union_find/partition_image.hpp"
#include "core/union_find/segment_contour.hpp"
#include "core/union_find/bool2d_canvas.hpp"
#include "core/gui/MultiWindowTrackBar.hpp"
#include <opencv2/opencv.hpp>

#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;
using namespace cv;


void help()
{
	cerr<<"Usage:\n";
	cerr<<"./partitiontest [image name]"<<endl;
	cerr<<"color map must be an interger between 0 and 12\n";
	cerr<<"for more information be sure to check:\n";
	cerr<<"https://docs.opencv.org/3.4.0/d3/d50/group__imgproc__colormap.html\n";
	exit(0);
}	

void func(cv::Mat &f, cv::Mat &n, const std::string &win)
{
	int black_white_mode = getTrackbarPos("bw",win);
	int num_ways = 4 * getTrackbarPos("num_ways",win);
	int color_map = getTrackbarPos("color_map",win);
	Bool2d array = create_bool2d(f);
	vector<PointSet> pp = partition_bool2d(array,black_white_mode >= 1, black_white_mode%2 == 0,num_ways);
	n = f.clone();
	n = Scalar::all(0);
	for(int i=0; i<pp.size();i++){

		uint8_t color = (uint8_t) ( ( 30 + (i+1) * 4)%255);
		for(Point point : pp[i]){
			n.at<uchar>(point.y,point.x) = color;
		}
	}
	if(color_map != 13) applyColorMap(n,n,color_map);
}





int main(int argc, char **argv)
{
	if(argc != 2 && argc != 3) help();
	Mat img = imread(argv[1]);
	if(img.empty()) help(); cvtColor(img,img,COLOR_BGR2GRAY);
	MultiWindowTrackBar mw(img);
	Mat outp = img.clone();
	mw.add_window(outp,"output",func);
	mw.add_trackbar_on_window("output","bw",0,2);
	mw.add_trackbar_on_window("output","num_ways",0,2);
	mw.add_trackbar_on_window("output","color_map",0,13);
	mw.autowork();
}














