#define _CRT_SECURE_NO_DEPRECATE //去除fopen報警告
#include <stdio.h> 
#include <cv.h> 
#include <highgui.h> 
#include <iostream>
#include <fstream>
#include <string>
using namespace cv;
using namespace std;
Mat erosion(Mat ori,int masksize);
Mat mirror(cv::Mat gray,int masksize);
Mat dilation(Mat ori,int masksize);
int count_coins(cv::Mat ori,int masksize,int num);
Mat count_errotion(Mat ori,int masksize);
Mat countt_dilation(Mat ori,int masksize);



void main()
{

unsigned char *coin ,*bike ,*calculator ;
char FileNameOri[]="coins_512x512.raw";
char FileNamebright[]="bike_900x672.raw";
char FileNamedark[]="calculator_360x240.raw";

coin = new unsigned char[512*512]; 
bike = new unsigned char[672*900]; 
calculator = new unsigned char[240*360]; 
 
CvMat *coinmat = cvCreateMat(512,512, CV_8UC1);
CvMat *bikemat = cvCreateMat(672,900, CV_8UC1);
CvMat *calculatormat = cvCreateMat(240,360, CV_8UC1);

FILE *BW256;
	BW256 = fopen(FileNameOri,"rb");
FILE *sine4_128;
	sine4_128 = fopen(FileNamebright,"rb");
FILE *sine16_128;
	sine16_128 = fopen(FileNamedark,"rb");


		fread(coin,1,512*512,BW256);
		cvSetData(coinmat,coin,coinmat->step);
		fread(bike,1,672*900,sine4_128);
		cvSetData(bikemat,bike,bikemat->step);
		fread(calculator,1,360*240,sine16_128);
		cvSetData(calculatormat,calculator,calculatormat->step);



cv::Mat dst;
dst = Mat(coinmat->rows,coinmat ->cols,coinmat->type,coinmat->data.fl);//轉換格式
cv::Mat bike_mat;
bike_mat = Mat(bikemat->rows,bikemat ->cols,bikemat->type,bikemat->data.fl);//轉換格式
cv::Mat cal_mat;
cal_mat = Mat(calculatormat->rows,calculatormat ->cols,calculatormat->type,calculatormat->data.fl);//轉換格式
	



	int number1=0;
	cout<<"輸入題號:例如1_a小題為11 2_a小題為21";
	cin>> number1;
	if( number1 ==11)
	{
		imshow("ooo",dst);
		Mat coin_erosion=erosion(dst,3);
		Mat coin_dilation=dilation(coin_erosion,25);
		imshow("第一次",coin_dilation);
		Mat coin_erosion2=erosion(coin_dilation,25);
		Mat coin_dilation2=dilation(coin_erosion2,3);
		imwrite("coin.png",coin_dilation2);
		imshow("第2次",coin_dilation2);
		cvWaitKey(0);
	}	

	if(number1==12)
	{
		Mat coin_erosion=count_errotion(dst,3);
	Mat coin_dilation=countt_dilation(coin_erosion,25);
		imshow("第一次",coin_dilation);
		Mat coin_dilation2=countt_dilation(coin_erosion,23);
		imshow("第2次",coin_dilation2);
		Mat count(512,512,CV_8U);
		for(int i =0;i<512;i++)
			for(int j=0;j<512;j++)
			{
		count.at<uchar>(i,j)=coin_dilation2.at<uchar>(i,j)-coin_dilation.at<uchar>(i,j);
		if(count.at<uchar>(i,j)==0)
		{
			count.at<uchar>(i,j)=255;
		}
		
			}

			int countcoin=0;
			Mat count_dilation=countt_dilation(count,3);
		for(int i =0;i<512;i++)
			for(int j=0;j<512;j++)
			{
				if(count_dilation.at<uchar>(i,j)==0)
		{
			countcoin++;
		}
		
			}
			imshow("第3次",count_dilation);
			printf("有%d個",countcoin);
		cvWaitKey(0);
	}

	if(number1==21)
	{

	//threshold(bike_mat,bike_mat,120,255,THRESH_BINARY);
				imshow("bike_mat",bike_mat);
	Mat bike_erosion(672,900,CV_8U);
	bike_erosion=erosion(bike_mat,5);

				imshow("第1",bike_erosion);
	Mat bike_edge(672,900,CV_8U);
		for(int i =0;i<672;i++)
			for(int j=0;j<900;j++)
			{
				bike_edge.at<uchar>(i,j)=bike_mat.at<uchar>(i,j)-bike_erosion.at<uchar>(i,j);
		
			}
			imwrite("BIKE.png",bike_edge);
			imshow("第3次",bike_edge);
		cvWaitKey(0);
	}


	if(number1=22)
	{
		Mat cal_erosion(240,360,CV_8U);
	cal_erosion=erosion(cal_mat,5);

				imshow("第",cal_erosion);
	Mat cal_edge(240,360,CV_8U);
		for(int i =0;i<240;i++)
			for(int j=0;j<360;j++)
			{
				cal_edge.at<uchar>(i,j)=cal_mat.at<uchar>(i,j)-cal_erosion.at<uchar>(i,j);
		
			}
	Mat cal_dilation(240,360,CV_8U);
	cal_dilation=dilation(cal_mat,5);
	Mat notext(240,360,CV_8U);
	notext=erosion(cal_dilation,5);
			imwrite("cal.png",cal_edge);
			imshow("第3次",notext);
    waitKey(0);

	}



	}
