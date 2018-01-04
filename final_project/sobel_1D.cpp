#include<iostream>
#include<cmath>
#include <WINDOWS.H>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<cuda_runtime.h>

#include <math.h>
using namespace std;
using namespace cv;

int image[100000000];
int f_image[100000000];

int gradient_x(int x, int y,int width)
{
	int gx;
	gx = image[(x - 1)*width + (y - 1)] * 1 + image[(x - 1)*width + y] * 2 + image[(x - 1)*width + (y + 1)] * 1 + image[(x + 1)*width + (y - 1)] * (-1) + image[(x + 1)*width + y] * (-2) + image[(x + 1)*width + (y + 1)] * (-1);
	return gx;
}

int gradient_y(int x, int y,int width)
{
	int gy;
	gy = image[(x - 1)*width + (y - 1)] * 1 + image[x*width + (y - 1)] * 2 + image[(x + 1)*width + (y - 1)] * 1 + image[(x - 1)*width + (y + 1)] * (-1) + image[x*width + (y + 1)] * (-2) + image[(x + 1)*width + (y + 1)] * (-1);
	return gy;
}

int gradient(int x, int y,int width)
{
	int a = gradient_x(x, y,width);
	int b = gradient_y(x, y,width);

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
			image[i*src.cols+j] = src.at<uchar>(i,j);
		}
	}

	//int**
	//cudaMalloc((void**)&cuda_image, sizeof(int) * 10000 * 10000);
	//cudaMalloc((void**)&cuda_f_image, sizeof(int) * 10000 * 10000);
	//cudaMemcpy(image,)

	int sum;
	for (int y = 1; y < src.rows - 1; y++) {
		for (int x = 1; x < src.cols - 1; x++) {
			sum = gradient(y,x, src.cols);
			//sum = sum > 255 ? 255 : sum;
			sum = sum > 100? 255 : 0;
			f_image[y*(src.cols)+x] = sum;
		}
	}

	
	for (int y = 1; y < src.rows - 1; y++) {
		for (int x = 1; x < src.cols - 1; x++) {
			dst.at<uchar>(y, x) = f_image[y*(src.cols)+x];
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
