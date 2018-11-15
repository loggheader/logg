#include "core/union_find/segment_contour.hpp"
#include "core/union_find/bool2d_canvas.hpp"
#include "core/union_find/partition_image.hpp"

using namespace std;
using namespace cv;


/*****************************************************************************
	a small kinda not needed function, used only for making code cleaner, its
	work could be easily performed from within other functions where it is used 
	to get results in O(1)	instead of O(n), but whatever we probably only win
	a few dozen microseconds by replacing it...
	*****************************************************************************/
bool contains_zero_point(PointSet &set)
{
	Point zero_point = Point(0,0);
	for(Point point : set){
		if(point == zero_point) return true;
	}
	return false;
}


/*****************************************************************************
	a more high level function to be used in order to segment a contour
	to multiple smaller ones.
	******************************************************************************/
void segment_contour_to_subsets(PointSetContour &contour, std::vector<PointSetContour> &output_sets)
{
	Point offset;
	Bool2d array = create_bool2d(contour,offset,true);
	vector<PointSetFilledShape> black_regions = partition_bool2d(array,false,true);
	print_points_to_boolean(array,contour,false,offset);
	for(PointSetFilledShape &black_region : black_regions){
		if(!contains_zero_point(black_region)){
			output_sets.push_back(get_contour_subset_surrounding_region(contour,black_region,offset,array));
		}
	}
}








/***************************** basic functions to grab the part of a contour that
			surrounds a region in a bool2d canvas. DO remember that contour needs to be offseted
			whereas region is already!
										***************************************/

PointSetContour get_contour_subset_surrounding_region(PointSetContour &contour, PointSetFilledShape &region, 
			cv::Point offset, int depth)
{
//	Bool2d array = create_bool2d(contour);










}




PointSetContour get_contour_subset_surrounding_region(PointSetContour &contour, PointSetFilledShape &region,
					cv::Point offset, Bool2d &array, int depth)
{
	PointSetContour retval;
	print_points_to_boolean(array,region,true);
	while(depth--){
		for(Point point : contour){
			if(bool2d_touches_true_no_bound_checking(array, point + offset)) retval.push_back(point);
		}
		print_points_to_boolean(array,retval,true,offset);
	}
	print_points_to_boolean(array,region,false);
	return retval;
}



















