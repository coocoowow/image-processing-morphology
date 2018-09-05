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






int count_coins(cv::Mat ori,int masksize,int num)
{
	int halfmasksize = masksize / 2;
	cv::Mat ori_mirror(ori.rows + masksize - 1, ori.cols + masksize - 1, CV_8UC1);
	ori_mirror=mirror(ori,masksize);

	int temp;
	int coinnum=0;
	//cv::Mat out(height, width, CV_8UC1);
	for (int i = 0; i<512; i++)
	{
		for (int j = 0; j<512; j++)
		{
			//orinum = ori.at<uchar>(i+halfmasksize, j+halfmasksize );
			int temp =0;
			for(int k =-halfmasksize;k<halfmasksize;k++)
			{
				for(int d =-halfmasksize;d<halfmasksize;d++)
				{
					if(ori_mirror.at<uchar>(i+halfmasksize+k,j+halfmasksize+d)==255)
					{
						temp++;
					}
				}
			}
			if(temp>=num)
			{
				coinnum++;
			}
			//out.at<uchar>(i,j)=temp;
		}
	}
	return coinnum;
}