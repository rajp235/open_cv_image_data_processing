#ifndef UTILITY_H
#define UTILITY_H

#include "../image/image.h"
#include <opencv2/opencv.hpp>
#include <sstream>
#include <math.h>

class utility
{
	public:
		utility();
		virtual ~utility();
		static std::string intToString(int number);
		static int checkValue(int value);
		static void addGrey(image &src, image &tgt, int value);
		static void binarize(image &src, image &tgt, int threshold);
		static void scale(image &src, image &tgt, float ratio);
		static void binarize(cv::Mat &src, cv::Mat &tgt, int x, int y, int sx, int sy);
		static void gray(cv::Mat &src, cv::Mat &tgt, int x, int y, int sx, int sy);
		static void sobel3(cv::Mat &src, cv::Mat &tgt, int x, int y, int sx, int sy);
		static void sobel5(cv::Mat &src, cv::Mat &tgt, int x, int y, int sx, int sy);
		static void coloredge(cv::Mat &src, cv::Mat &tgt, int k, int x, int y, int sx, int sy);
		static void binaryedge(cv::Mat &src, cv::Mat &tgt, int thres, int angle, int x, int y, int sx, int sy);
		static void cannycv(cv::Mat &src, cv::Mat &tgt, int x, int y, int sx, int sy);
		static void histoeq(cv::Mat &src, cv::Mat &tgt, int x, int y, int sx, int sy);
		static void cannyhisto(cv::Mat &src, cv::Mat &tgt, int x, int y, int sx, int sy);
		static void otsucv(cv::Mat &src, cv::Mat &tgt, int x, int y, int sx, int sy);
		static void otsuhisto(cv::Mat &src, cv::Mat &tgt, int x, int y, int sx, int sy);
		static void QRcode(cv::Mat &src, cv::Mat &tgt, int x, int y, int sx, int sy);
		static void QRcodqul(cv::Mat &src, cv::Mat &tgt, int x, int y, int sx, int sy);
		static void avgblur(cv::Mat &src, cv::Mat &tgt, int WindowSize, int x, int y, int sx, int sy);
};

#endif
