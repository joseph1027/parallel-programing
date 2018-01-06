#include<iostream>
#include<cmath>
#include <WINDOWS.H>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<time.h>

// includes, cuda
#include <vector_types.h>
#include <driver_functions.h>
#include <cuda_runtime.h>
#include <cuda_gl_interop.h>

// CUDA utilities and system includes
#include <helper_cuda.h>
#include <helper_cuda_gl.h>
#include <helper_functions.h>
#include <vector_types.h>
#include <math.h>
using namespace std;
using namespace cv;

int image[200000000];
int f_image[200000000];

/*__global__ void gradient_x(int x, int y,int width)
{
int gx;
gx = image[(x - 1)*width + (y - 1)] * 1 +
image[(x - 1)*width + y] * 2 +
image[(x - 1)*width + (y + 1)] * 1 +
image[(x + 1)*width + (y - 1)] * (-1) +
image[(x + 1)*width + y] * (-2) +
image[(x + 1)*width + (y + 1)] * (-1);
}
__global__ void gradient_y(int x, int y,int width)
{
int gy;
gy = image[(x - 1)*width + (y - 1)] * 1 +
image[x*width + (y - 1)] * 2 +
image[(x + 1)*width + (y - 1)] * 1 +
image[(x - 1)*width + (y + 1)] * (-1) +
image[x*width + (y + 1)] * (-2) +
image[(x + 1)*width + (y + 1)] * (-1);
}*/

__global__ void gradient(int* image, int* f_image, int length, int width)
{
	//int a = gradient_x(x, y,width);
	//int b = gradient_y(x, y,width);
	int templates[25] = { 
		1, 4, 7, 4, 1,

		4, 16, 26, 16, 4,

		7, 26, 41, 26, 7,

		4, 16, 26, 16, 4,

		1, 4, 7, 4, 1 };

	int id = blockIdx.x*blockDim.x + threadIdx.x;
	if (id >= length*width)
	{
		return;
	}

	int y = id / width;
	int x = id % width;
	if (y < 2 || y >= length - 2 || x < 2 || x >= width - 2)
	{
		return;
	}
	/*
	int a = image[(y - 1)*width + (x - 1)] * 1 +
		image[(y - 1)*width + x] * 2 +
		image[(y - 1)*width + (x + 1)] * 1 +
		image[(y + 1)*width + (x - 1)] * (-1) +
		image[(y + 1)*width + x] * (-2) +
		image[(y + 1)*width + (x + 1)] * (-1);

	int b = image[(y - 1)*width + (x - 1)] * 1 +
		image[y*width + (x - 1)] * 2 +
		image[(y + 1)*width + (x - 1)] * 1 +
		image[(y - 1)*width + (x + 1)] * (-1) +
		image[y*width + (x + 1)] * (-2) +
		image[(y + 1)*width + (x + 1)] * (-1);

	int g = sqrt(float(a*a + b*b));

	g = g > 100 ? 255 : 0;
	f_image[y*width + x] = g;*/
	int g = 0;
	int index = 0;
	for (int m = y - 2; m<y + 3; m++)
	{
		for (int n = x - 2; n<x + 3; n++)
		{
			g += image[m*width + n] * templates[index++];
		}
	}
	g /= 273;
	if (g > 255)
		g = 255;
	f_image[id] = g;
}


int main()
{
	//double a = clock();
	Mat src;
	src = imread("D:\\testpic\\2.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat dst = src.clone();
	for (int y = 0; y < src.rows; y++)
		for (int x = 0; x < src.cols; x++)
			dst.at<uchar>(y, x) = 0.0;
	/////////////////////////////////////////////
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			image[i*src.cols + j] = src.at<uchar>(i, j);
		}
	}
	int image_size = src.rows*src.cols;
	int* cuda_image;
	int* cuda_f_image;
	double time_sum = 0;
	for (int h = 0; h < 10; h++)
	{
		double a = clock();
		cudaMalloc((void**)&cuda_image, sizeof(int) * src.cols * src.rows);
		cudaMalloc((void**)&cuda_f_image, sizeof(int) * src.cols * src.rows);
		cudaMemcpy(cuda_image, image, sizeof(int) * src.rows * src.cols, cudaMemcpyHostToDevice);
		gradient << <(image_size / 64) + 1, 64 >> > (cuda_image, cuda_f_image, src.rows, src.cols);
		cudaMemcpy(f_image, cuda_f_image, sizeof(int) * src.rows * src.cols, cudaMemcpyDeviceToHost);
		double b = clock();
		double diff = (b - a) / CLOCKS_PER_SEC;
		//cout << diff << endl;
		time_sum += diff;
	}
	cout << time_sum / 10 <<endl;


	for (int y = 0; y < src.rows ; y++) {
		for (int x = 0; x < src.cols ; x++) {
			dst.at<uchar>(y, x) = f_image[y*(src.cols) + x];
		}
	}

	cout << src.rows << endl;
	cout << src.cols << endl;

	namedWindow("initial", WINDOW_NORMAL);
	imshow("initial", src);

	namedWindow("final", WINDOW_NORMAL);
	imshow("final", dst);

	//double b = clock();
	//double diff = (b - a) / CLOCKS_PER_SEC;
	//cout << diff << endl;

	waitKey();
}
