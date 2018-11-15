#ifndef header_segment_contour_hpp
#	define header_segment_contour_hpp


#	include "core/misc/misc.hpp"


/****************************** define's ************************************/
#	define UNION_DEPTH_DEFAULT 2



///////////////////////////////////////////////////////////////////////////////////
void segment_contour_to_subsets(PointSetContour &contour, std::vector<PointSetContour> &output_sets);







//////////////////////////////////////////////////////////////////////////////////
PointSet get_contour_subset_surrounding_region(PointSetContour &contour, PointSetFilledShape &region, 
					cv::Point offset, int depth = UNION_DEPTH_DEFAULT);
PointSet get_contour_subset_surrounding_region(PointSetContour &contour, PointSetFilledShape &region,
					cv::Point offset, Bool2d &array, int depth = UNION_DEPTH_DEFAULT);





#endif