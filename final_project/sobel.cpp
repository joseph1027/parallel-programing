#include<iostream>
#include<cmath>
#include <WINDOWS.H>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
//#include<cuda_runtime.h>

#include <math.h>
using namespace std;
using namespace cv;

int image[10000][10000];
int f_image[10000][10000];

int gradient_x(int x, int y)
{
	int gx;
	gx = image[x - 1][y - 1] * 1 + image[x - 1][y] * 2 + image[x - 1][y + 1] * 1 + image[x + 1][y - 1] * (-1) + image[x + 1][y] * (-2) + image[x + 1][y + 1] * (-1);
	return gx;
}

int gradient_y(int x, int y)
{
	int gy;
	gy = image[x - 1][y - 1] * 1 + image[x][y - 1] * 2 + image[x + 1][y - 1] * 1 + image[x - 1][y + 1] * (-1) + image[x][y + 1] * (-2) + image[x + 1][y + 1] * (-1);
	return gy;
}

int gradient(int x, int y)
{
	int a = gradient_x(x, y);
	int b = gradient_y(x, y);

	int g = sqrt(a*a + b*b);
	return g;
}


int main()
{
	Mat src;
	src = imread("D:\\testpic\\656029.png",CV_LOAD_IMAGE_GRAYSCALE);
	Mat dst = src.clone();
	for (int y = 0; y < src.rows; y++)
		for (int x = 0; x < src.cols; x++)
			dst.at<uchar>(y, x) = 0.0;
	/////////////////////////////////////////////
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			image[i][j] = src.at<uchar>(i,j);
		}
	}

	int sum;
	for (int y = 1; y < src.rows - 1; y++) {
		for (int x = 1; x < src.cols - 1; x++) {
			sum = gradient(y, x);
			//sum = sum > 255 ? 255 : sum;
			sum = sum > 100? 255 : 0;
			f_image[y][x] = sum;
		}
	}

	
	for (int y = 1; y < src.rows - 1; y++) {
		for (int x = 1; x < src.cols - 1; x++) {
			dst.at<uchar>(y, x) = f_image[y][x];
		}
	}

	cout << src.rows << endl;
	cout << src.cols << endl;

	namedWindow("initial", WINDOW_NORMAL);
	imshow("initial", src);

	namedWindow("final", WINDOW_NORMAL);
	imshow("final", dst);


	
	waitKey();
}
