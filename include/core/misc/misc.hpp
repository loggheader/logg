#ifndef header_misc_hpp
#	define header_misc_hpp

#	include <opencv2/core/core.hpp>
#	include <vector>


/*
	some helpful but not fully needed typedefs for vectors
*/

typedef std::vector<bool> Bool1d;
typedef std::vector< std::vector<bool> > Bool2d;



/*
	some typedefs to diferentiate between different usages of
	vector<point>
*/

typedef std::vector<cv::Point> Curve;
typedef std::vector<cv::Point> PointSet;
typedef std::vector<cv::Point> PointSetContour;
typedef std::vector<cv::Point> PointSetFilledShape;



/*
	some typedefs for images
*/

typedef cv::Mat BinaryMat;
typedef cv::Mat LabelMat;









#endif