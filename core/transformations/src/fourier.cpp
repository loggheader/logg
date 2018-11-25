#include <iostream>
#include <opencv2/opencv.hpp>
#include "core/transformations/fourier.hpp"

//inverse and normal discrete fourier transformation
//In order to use it: #include "core/transformations/fourier.hpp"


void compute_dft(cv::Mat &in, cv::Mat &complex)
{
  cv::Mat padded;
  int m = getOptimalDFTSize( in.rows );
  int n = getOptimalDFTSize( in.cols );
  copyMakeBorder(in, padded, 0, m - in.rows, 0, n - in.cols, cv::BORDER_CONSTANT, Scalar::all(0));
  cv::Mat planes[] = {cv::Mat_<float>(padded), cv::Mat::zeros(padded.size(), CV_32F)};
  merge(planes, 2, complex);
  dft(complex, complex, cv::DFT_COMPLEX_OUTPUT);  
}

void compute_idft(cv::Mat &out, cv::Mat &complex)
{
  idft(complex, out);
  cv::Mat planes[] = {
      cv::Mat::zeros(complex.size(), CV_32F),
      cv::Mat::zeros(complex.size(), CV_32F)
  };
  split(out, planes); // planes[0] = Re(DFT(I)), planes[1] = Im(DFT(I))
  magnitude(planes[0], planes[1], out); // sqrt(Re(DFT(I))^2 + Im(DFT(I))^2)
  normalize(out, out, 0, 1, cv::NORM_MINMAX);
}
