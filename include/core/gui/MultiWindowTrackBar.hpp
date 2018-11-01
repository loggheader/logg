#ifndef header_MultiWindowTrackBar_hpp
#	define header_MultiWindowTrackBar_hpp

#	include <vector>
#	include <string>
#	include <opencv2/core.hpp>


typedef void (*NextImage) (cv::Mat &, cv::Mat &, const std::string &);


class MultiWindowTrackBar{
public:
	MultiWindowTrackBar(cv::Mat & original_image, std::string origin_name = "original");
	void add_window(cv::Mat& _image, const std::string & _winName, NextImage _compute_next_image);
	void add_trackbar_on_window(const std::string & _winName, const std::string & _trackbar, int min_track_val, int max_track_val);
	void compute_all_images();
	void autowork();
	static MultiWindowTrackBar * global_ptr;
	static void MultiWindowTrackBar_on_change(int, void *);
private:
	std::vector<std::string> winName;
	std::vector<cv::Mat *> image;
	std::vector<std::vector<std::string> > trackbarName;
	std::vector<std::vector<std::pair<int,int> > > trackbarDimensions;
	std::vector<std::vector<int> > trackvalue;
	std::vector<NextImage> compute_next_image;

};





#endif