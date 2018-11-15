#ifndef header_bool2d_canvas_hpp
#	define header_bool2d_canvas_hpp

#	include "core/misc/misc.hpp"



/*********************************
	define constants
********************************/
#	define OFFSET_AROUND_DEFAULT 4
#	define OFFSET_AROUND_HALF 2
#	define UNION_DEPTH_DEFAULT 2


/**********************************
	constructors
**********************************/
Bool2d create_bool2d(int num_row, int num_col, bool value = false);
Bool2d create_bool2d(PointSet &set, cv::Point &offset, bool value = false, int looseness = OFFSET_AROUND_DEFAULT);
Bool2d create_bool2d(cv::Mat &img);

void create_bool2d(Bool2d &array, int num_row, int num_col, bool value = false);
void create_bool2d(Bool2d &array, PointSet &set, cv::Point &offset, bool value = false, int looseness = OFFSET_AROUND_DEFAULT);
void create_bool2d(Bool2d &array, cv::Mat &img);


/***********************************
	functions for printing
***********************************/
void print_points_to_boolean(Bool2d &array, PointSet &points, bool value, cv::Point offset = cv::Point(0,0));


/*********************************
	basic neighbourhood processing
**********************************/
bool bool2d_touches_true_no_bound_checking(Bool2d &array, int row, int col);
bool bool2d_touches_true_no_bound_checking(Bool2d &array, cv::Point point);



//cv::Rect loose_bounding_rect(PointSet &contour, Bool2d &array);
//cv::Point make_boolean_array_out_of_ROI(std::vector<cv::Point> &contour, std::vector<std::vector<bool> > &array);







#endif