#include "core/union_find/bool2d_canvas.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <cassert>

using namespace std;
using namespace cv;



/***************************************************************************************************
											constructors
**************************************************************************************************/
void create_bool2d(Bool2d &array, int num_row, int num_col, bool value)
{
	array.clear();
	array.resize(num_row);
	for(int i=0;i<num_row;i++) array[i].resize(num_col,value);
}


void create_bool2d(Bool2d &array, PointSet &set, cv::Point &offset, bool value, int looseness)
{
	assert(looseness % 2 == 0);
	Rect rect = boundingRect(set);
	create_bool2d(array,rect.height+looseness,rect.width+looseness,!value);
	offset = Point(looseness/2 - rect.x, looseness/2 - rect.y);
	print_points_to_boolean(array,set,value,offset);
}

void create_bool2d(Bool2d &array, cv::Mat &img)
{
	assert(img.channels() == 1);
	create_bool2d(array,img.rows,img.cols,false);
	for(int i=0; i<img.rows; i++){
		for(int j=0;j<img.cols;j++){
			array[i][j] = (img.at<uchar>(i,j) <128)? 0 : 255;
		}
	}
}


Bool2d create_bool2d(int num_row, int num_col, bool value)
{
	Bool2d array;
	create_bool2d(array,num_row,num_col,value);
	return array;
}

Bool2d create_bool2d(PointSet &set, cv::Point &offset, bool value, int looseness)
{
	Bool2d array;
	create_bool2d(array,set,offset,value,looseness);
	return array;
}

Bool2d create_bool2d(cv::Mat &img)
{
	Bool2d array;
	create_bool2d(array,img);
	return array;
}


/******************************************************************************************
									printing functions
**********************************************************************************************/

void print_points_to_boolean(Bool2d &array, PointSet &points, bool value, cv::Point offset)
{
	for(Point point : points){
		array[point.y + offset.y][point.x + offset.x] = value;
	}
}


/*******************************************************************************************
									basic procesing function
*******************************************************************************************/
bool bool2d_touches_true_no_bound_checking(Bool2d &array, int row, int col)
{
	return (array[row-1][col-1] || array[row-1][col] || array[row-1][col+1] ||
		                array[row][col-1] || array[row][col+1] ||
		   array[row+1][col-1] || array[row+1][col] || array[row+1][col+1]) && (array[row][col] == false);
}


bool bool2d_touches_true_no_bound_checking(Bool2d &array, cv::Point point)

{
	int row = point.y;
	int col = point.x;

	return (array[row-1][col-1] || array[row-1][col] || array[row-1][col+1] ||
		                array[row][col-1] || array[row][col+1] ||
		   array[row+1][col-1] || array[row+1][col] || array[row+1][col+1]) && (array[row][col] == false);
}





