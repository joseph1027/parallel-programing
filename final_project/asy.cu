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

__global__ void gradient(int* image, int* f_image,int padding, int width, int length)
{
	//int a = gradient_x(x, y,width);
	//int b = gradient_y(x, y,width);
	int id = (blockIdx.x*blockDim.x + threadIdx.x)+padding;
	if (blockIdx.x*blockDim.x + threadIdx.x >= width)
	{
		return;
	}

	int y = id / width;
	int x = id % width;
	if (y == 0 || y == length - 1 || x == 0 || x == width - 1)
	{
		return;
	}
	int a = image[(y - 1)*width + (x - 1)] +
		image[(y - 1)*width + x] * 2 +
		image[(y - 1)*width + (x + 1)] -
		image[(y + 1)*width + (x - 1)] -
		image[(y + 1)*width + x] * 2 -
		image[(y + 1)*width + (x + 1)];

	int b = image[(y - 1)*width + (x - 1)] +
		image[y*width + (x - 1)] * 2 +
		image[(y + 1)*width + (x - 1)] -
		image[(y - 1)*width + (x + 1)] -
		image[y*width + (x + 1)] * 2 -
		image[(y + 1)*width + (x + 1)];

	int g = sqrt(float(a*a + b*b));

	g = g > 100 ? 255 : 0;
	f_image[id] = g;

}


int main()
{
	Mat src;
	src = imread("D:\\testpic\\666.png", CV_LOAD_IMAGE_GRAYSCALE);
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

	int* cuda_image;
	int* cuda_f_image;
	cudaMalloc((void**)&cuda_image, sizeof(int) * src.rows * src.cols);
	cudaMalloc((void**)&cuda_f_image, sizeof(int) * src.rows * src.cols);
	cudaStream_t streams[32];
	for (int i = 0; i < 4; i++)
	{
		cudaStreamCreate(&streams[i]);
	}
	double a = clock();
	cudaMemcpyAsync(cuda_image + 0 * src.cols, image, sizeof(int)*src.cols, cudaMemcpyHostToDevice, streams[0]);
	cudaMemcpyAsync(cuda_image + 1 * src.cols, image + 1 * src.cols , sizeof(int)*src.cols, cudaMemcpyHostToDevice, streams[0]);
	for (int i = 1; i < src.rows - 1; i++) {
		cudaMemcpyAsync(cuda_image + (i + 1) * src.cols, image+(i + 1)*src.cols, sizeof(int) * src.cols, cudaMemcpyHostToDevice, streams[i & 3]);
		 gradient<<<(src.cols + 127) >> 7, 128, 0, streams[i & 3] >> >(cuda_image, cuda_f_image, i * src.cols, src.cols, src.rows);
	}
	for (int i = 1; i < src.rows - 1; i++) {
		cudaMemcpyAsync(f_image + i*src.cols, cuda_f_image + i * src.cols, sizeof(int) * src.cols, cudaMemcpyDeviceToHost, streams[i & 3]);
	}
	for (int i = 0; i < 4; i++)
		cudaStreamSynchronize(streams[i]);

	
	//cudaMemcpy(cuda_image, image, sizeof(int) * src.rows * src.cols, cudaMemcpyHostToDevice);

	//int image_size = src.rows*src.cols;
	//gradient <<<(image_size / 2048) + 1, 1024 >>> (cuda_image, cuda_f_image, src.rows, src.cols);

	//(f_image, cuda_f_image, sizeof(int) * src.rows * src.cols, cudaMemcpyDeviceToHost);
	double b = clock();
	double diff = (b - a) / CLOCKS_PER_SEC;
	cout << diff << endl;



	for (int y = 1; y < src.rows - 1; y++) {
		for (int x = 1; x < src.cols - 1; x++) {
			dst.at<uchar>(y, x) = f_image[y*(src.cols) + x];
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
