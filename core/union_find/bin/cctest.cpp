#include <opencv2/opencv.hpp>
#include "core/misc/misc.hpp"
#include "core/union_find/partition_image.hpp"
#include <iostream>
#include <cstdlib>

using namespace std;
using namespace cv;


void help()
{	
	cout <<"Error! Usage:\n"<<"./cctest [image name]\n"<<endl;
	exit(0);
}	

int main(int argc, char **argv)
{
	if(argc != 2) help();
	Mat img = imread(argv[1]); if(img.empty()) help();
	cvtColor(img,img,COLOR_BGR2GRAY);
	int xx;
	Mat tt(img.size(),CV_8UC1,6);
	Mat labels = label_connected_components(img,xx,8,true);
	labels.convertTo(labels,CV_8UC1,1);
	multiply(labels,tt,labels);
	applyColorMap(labels,labels,4);
	imshow("hello",labels);
	waitKey(0);
	cout<<xx<<endl;
}