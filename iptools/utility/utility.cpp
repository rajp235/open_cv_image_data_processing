#include "utility.h"

#define MAXRGB 255
#define MINRGB 0

using namespace cv;

std::string utility::intToString(int number)
{
   std::stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

int utility::checkValue(int value)
{
	if (value > MAXRGB)
		return MAXRGB;
	if (value < MINRGB)
		return MINRGB;
	return value;
}

/*-----------------------------------------------------------------------**/
void utility::addGrey(image &src, image &tgt, int value)
{
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			tgt.setPixel(i,j,checkValue(src.getPixel(i,j)+value)); 
		}
}

/*-----------------------------------------------------------------------**/
void utility::binarize(image &src, image &tgt, int threshold)
{
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++)
	{
		for (int j=0; j<src.getNumberOfColumns(); j++)
		{
			if (src.getPixel(i,j) < threshold)
				tgt.setPixel(i,j,MINRGB);
			else
				tgt.setPixel(i,j,MAXRGB);
		}
	}
}

/*-----------------------------------------------------------------------**/
void utility::scale(image &src, image &tgt, float ratio)
{
	int rows = (int)((float)src.getNumberOfRows() * ratio);
	int cols  = (int)((float)src.getNumberOfColumns() * ratio);
	tgt.resize(rows, cols);
	for (int i=0; i<rows; i++)
	{
		for (int j=0; j<cols; j++)
		{	
			int i2 = (int)floor((float)i/ratio);
			int j2 = (int)floor((float)j/ratio);
			if (ratio == 2) {
				tgt.setPixel(i,j,checkValue(src.getPixel(i2,j2)));
			}

			if (ratio == 0.5) {
				int value = src.getPixel(i2,j2) + src.getPixel(i2,j2+1) + src.getPixel(i2+1,j2) + src.getPixel(i2+1,j2+1);
				tgt.setPixel(i,j,checkValue(value/4));
			}
		}
	}
}




/*-----------------------------------------------------------------------**/
void utility::gray(Mat &src, Mat &tgt, int x, int y, int sx, int sy)
{
	cvtColor(src, tgt, COLOR_BGR2GRAY);
}

/*-----------------------------------------------------------------------**/
void utility::binarize(Mat &src, Mat &tgt, int x, int y, int sx, int sy)
{
	Mat tmp;
	Rect r(x,y,sx,sy);
	cvtColor(src(r),tmp,COLOR_BGR2GRAY);
	threshold(tmp,tmp,128,255,THRESH_BINARY);
	cvtColor(tmp,tmp,COLOR_GRAY2BGR);
	tmp.copyTo(tgt(r));
}

/*-----------------------------------------------------------------------**/
void utility::sobel3(Mat &src, Mat &tgt, int x, int y, int sx, int sy)
{
	Mat tmp;
	Rect r(x,y,sx,sy);
	Sobel(src(r),tmp,-1,1,1,3);
	tmp.copyTo(tgt(r));
}

/*-----------------------------------------------------------------------**/
void utility::sobel5(Mat &src, Mat &tgt, int x, int y, int sx, int sy)
{
	Mat tmp;
	Rect r(x,y,sx,sy);
	Sobel(src(r),tmp,-1,1,1,5);
	tmp.copyTo(tgt(r));
}

/*-----------------------------------------------------------------------**/
void utility::coloredge(Mat &src, Mat &tgt, int k, int x, int y, int sx, int sy)
{
	Mat tmp;
	Rect r(x,y,sx,sy);
	cvtColor(src(r), tmp, COLOR_BGR2HSV);
	vector<Mat> hsvValues;
	split(tmp, hsvValues);
	Mat tmp2;
	Sobel(hsvValues[2],tmp2,-1,1,1,k);
	cvtColor(tmp2,tmp2,COLOR_GRAY2BGR);
	tmp2.copyTo(tgt(r));
}

/*-----------------------------------------------------------------------**/
void utility::binaryedge(Mat &src, Mat &tgt, int thres, int angle, int x, int y, int sx, int sy)
{
	Mat tmp;
	Mat sobx;
	Mat soby;
	Rect r(x,y,sx,sy);
	cvtColor(src(r), tmp, COLOR_BGR2GRAY);
	Sobel(tmp,sobx,CV_64F,1,0,5);
	Sobel(tmp,soby,CV_64F,0,1,5);
	for(int i = 0; i < tmp.rows; i++)
	{
		for(int j = 0; j < tmp.cols; j++)
		{
			double gx = sobx.at<double>(i,j);
			double gy = soby.at<double>(i,j);
			double angleD = atan2(gx,gy);
			angleD = angleD*180.0/CV_PI;
			if(angleD < 0)
				angleD = angleD + 180;

			if(angleD >= angle - 10.0 && angleD <= angle + 10.0)
			{
				tmp.at<uchar>(i,j) = 255;
			}
			else
			{
				tmp.at<uchar>(i,j) = 0;
			}
		}
	}
	cvtColor(tmp,tmp,COLOR_GRAY2BGR);
	tmp.copyTo(tgt(r));
}

/*-----------------------------------------------------------------------**/
void utility::cannycv(Mat &src, Mat &tgt, int x, int y, int sx, int sy)
{
	Mat tmp;
	Rect r(x,y,sx,sy);
	cvtColor(src(r),tmp,COLOR_BGR2GRAY);
	Canny(tmp,tmp,100,200,3);
	cvtColor(tmp,tmp,COLOR_GRAY2BGR);
	tmp.copyTo(tgt(r));

	// coloredge(src,tgt,5,x,y,sx,sy);
}

/*-----------------------------------------------------------------------**/
void utility::histoeq(Mat &src, Mat &tgt, int x, int y, int sx, int sy)
{
	Mat tmp;
	Rect r(x,y,sx,sy);
	cvtColor(src(r),tmp,COLOR_BGR2GRAY);
	equalizeHist(tmp,tmp);
	cvtColor(tmp,tmp,COLOR_GRAY2BGR);
	tmp.copyTo(tgt(r));

	// cvtColor(src,tgt,COLOR_BGR2GRAY);
}

/*-----------------------------------------------------------------------**/
void utility::cannyhisto(Mat &src, Mat &tgt, int x, int y, int sx, int sy)
{
	Mat tmp;
	Rect r(x,y,sx,sy);
	cvtColor(src(r),tmp,COLOR_BGR2GRAY);
	equalizeHist(tmp,tmp);
	Canny(tmp,tmp,100,200,3);
	cvtColor(tmp,tmp,COLOR_GRAY2BGR);
	tmp.copyTo(tgt(r));
}

void utility::otsucv(Mat &src, Mat &tgt, int x, int y, int sx, int sy)
{
	Mat tmp;
	Rect r(x,y,sx,sy);
	cvtColor(src(r),tmp,COLOR_BGR2GRAY);
	threshold(tmp,tmp,0,255,THRESH_OTSU);
	cvtColor(tmp,tmp,COLOR_GRAY2BGR);
	tmp.copyTo(tgt(r));
}

void utility::otsuhisto(Mat &src, Mat &tgt, int x, int y, int sx, int sy)
{
	Mat tmp;
	Rect r(x,y,sx,sy);
	cvtColor(src(r),tmp,COLOR_BGR2GRAY);

	int thre = threshold(tmp,tmp,0,255,THRESH_OTSU);
	cout << thre << endl;

	cvtColor(tmp,tmp,COLOR_GRAY2BGR);
	tmp.copyTo(tgt(r));
}

void utility::QRcode(Mat &src, Mat &tgt, int x, int y, int sx, int sy)
{
	Mat tmp;
	Mat tmp2;
	Rect r(x,y,sx,sy);
	cvtColor(src(r),tmp,COLOR_BGR2GRAY);
	QRCodeDetector qr_code;
	std::string c = qr_code.detectAndDecode(tmp,tmp,tmp2);
	if (c.length() > 0)
	{
		cout << c << endl;
		cvtColor(tmp2,tmp2,COLOR_GRAY2BGR);
		resize(tmp2,tmp2,Size(150,150),0,0,INTER_AREA);
		tgt = tmp2;
	}
	else
	{
		cout << "Cannot read QRCode" << endl;
	}
}

void utility::QRcodqul(Mat &src, Mat &tgt, int x, int y, int sx, int sy)
{
	Mat tmp;
	Mat tmp2;
	Rect r(x,y,sx,sy);
	cvtColor(src(r),tmp,COLOR_BGR2GRAY);
	equalizeHist(tmp,tmp);
	QRCodeDetector qr_code;
	std::string c = qr_code.detectAndDecode(tmp,tmp,tmp2);
	if (c.length() > 0)
	{
		cout << c << endl;
		cvtColor(tmp2,tmp2,COLOR_GRAY2BGR);
		resize(tmp2,tmp2,Size(150,150),0,0,INTER_AREA);
		tgt = tmp2;
	}
	else
	{
		cout << "Cannot read QRCode" << endl;
	}
}

/*-----------------------------------------------------------------------**/
void utility::avgblur(Mat &src, Mat &tgt, int WindowSize, int x, int y, int sx, int sy)
{
	blur(src,tgt,Size(WindowSize,WindowSize));
}
