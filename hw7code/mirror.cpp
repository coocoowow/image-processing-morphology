#define _CRT_SECURE_NO_DEPRECATE //去除fopen報警告
#include <stdio.h> 
#include <cv.h> 
#include <highgui.h> 
#include <iostream>
#include <fstream>
#include <string>
using namespace cv;
using namespace std;









cv::Mat mirror(cv::Mat gray,int masksize)
{
	int halfmasksize = masksize / 2;
	cv::Mat out(gray.rows + masksize - 1, gray.cols + masksize - 1, CV_8UC1);
	for (int i = 0; i<out.rows; i++)
	{
		for (int j = 0; j<out.cols; j++)
		{
			if(i<halfmasksize&&j<halfmasksize)
			{
				out.at<uchar>( i, j) = 0;
			}
			else if(i>(out.rows-halfmasksize-1)&&j<halfmasksize)
			{
				out.at<uchar>( i, j) = 0;
			}
			else if(i<halfmasksize&&j>(out.cols-halfmasksize-1))
			{
				out.at<uchar>( i, j) = 0;
			}
			else if(i>(out.rows-halfmasksize-1)&&j>(out.cols-halfmasksize-1))
			{
				out.at<uchar>( i, j) = 0;
			}
			else if(i<halfmasksize)
			{
				out.at<uchar>( i, j) = 0;
			}
			else if(j<halfmasksize)
			{
				out.at<uchar>( i, j) = 0;
			}
			else if(i>(out.rows-halfmasksize-1))
			{
				out.at<uchar>( i, j) = 0;
			}
			else if(j>(out.cols-halfmasksize-1))
			{
				out.at<uchar>( i, j) = 0;
			}
			else 
			{
				out.at<uchar>(i,j) = gray.at<uchar>(i-halfmasksize, j-halfmasksize );
			}
		}

	}	
	
	return out;
}