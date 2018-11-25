#ifndef FOURIER_HPP
#define FOURIER_HPP

void compute_dft(cv::Mat &in, cv::Mat &complex);
void compute_idft(cv::Mat &out, cv::Mat &complex);

#endif
