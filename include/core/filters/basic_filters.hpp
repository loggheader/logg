#ifndef BASIC_FILTERS_HPP
#define BASIC_FILTERS_HPP

void derivatives(cv::Mat &in, cv::Mat &out, int kernel_size, int scale, int delta_value);
void brightness_contrast_gamma(cv::Mat &in ,cv::Mat &out, double gamma_value);
void brightness_contrast_alpha_beeta(cv::Mat &in ,cv::Mat &out,int alpha_value,int beeta_value);


#endif
