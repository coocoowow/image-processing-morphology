#define _CRT_SECURE_NO_DEPRECATE //去除fopen報警告
#include <stdio.h> 
#include <cv.h> 
#include <highgui.h> 
#include <iostream>
#include <fstream>
#include <string>
using namespace cv;
using namespace std;
Mat mirror(cv::Mat gray,int masksize);



cv::Mat count_errotion(Mat ori,int masksize)
{
	int halfmasksize = masksize / 2;
	cv::Mat ori_mirror(ori.rows + masksize - 1, ori.cols + masksize - 1, CV_8UC1);
	ori_mirror=mirror(ori,masksize);

	//int orinum;
	int temp;
	cv::Mat out(ori.rows, ori.cols, CV_8UC1);
	for (int i = 0; i<out.rows; i++)
	{
		for (int j = 0; j<out.cols; j++)
		{
			//orinum = ori.at<uchar>(i+halfmasksize, j+halfmasksize );
			temp =255;
			for(int k =-halfmasksize;k<halfmasksize;k++)
			{
				for(int d =-halfmasksize;d<halfmasksize;d++)
				{
					if(ori_mirror.at<uchar>(i+halfmasksize+k,j+halfmasksize+d)<200)
					{
						temp=0;
					}
					
				}
			}
			out.at<uchar>(i,j)=temp;
		}
	}
	return out;
}