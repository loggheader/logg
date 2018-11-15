#ifndef header_partition_image_hpp
#	define header_partition_image_hpp

#	include "core/misc/misc.hpp"

////////////////////////////////////////////
std::vector<PointSet> partition_bool2d(Bool2d &array, bool white, bool black, int num_ways = 0 , cv::Point offset = cv::Point());





////////////////////////////////////////////
//cv::Mat partition_binary_image(cv::Mat &img, std::vector<PointSet> &sets,bool white_or_black, bool labels = false);


cv::Mat label_connected_components(const cv::Mat &_img, int &num_labels, int num_ways, bool white_or_black);
std::vector<PointSet> get_pointsets_from_labels(LabelMat &labels, int num_labels);










#endif