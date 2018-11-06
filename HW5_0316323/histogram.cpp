#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>
#include <fstream>  
#include <CL/cl.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <vector>

const char* programSource =   
    "__kernel                                                         \n"  
    "void hist(__global int *A,                                       \n"  
    "          __global int *C)                                       \n"  
    "{                                                                \n"  
    "    int idx = get_global_id(0);                                  \n"  
    "    atomic_inc(&C[(idx % 3) * 256 + A[idx]]);                    \n"  
    "}                                                                \n"  
    ;  

char *ptr;
char *endd;
char buffer[1<<30];
int fd;

char my_getchar(char *&ptr,char *&endd)
{
    if(ptr == endd)
    {
        ptr = buffer;
        endd = buffer + read(fd,buffer,1<<30);
    }
    //std::cout<<*(ptr++)<<endl;
    return *(ptr++);
}

unsigned int get_value(char* &ptr,char* &endd)
{
    char ch;
    unsigned int value = 0;
    while(ch>'9'||ch<'0')
    {
        //std::cout<<"GG"<<endl;
        ch = my_getchar(ptr,endd);
    }
    while(ch>='0'&&ch<='9')
    {
        value = value*10 + (ch-'0');
        ch = my_getchar(ptr,endd);
        //std::cout<<value<<endl;
    }
    return value;
}


int main() 
{  
    unsigned int *A = NULL;
    unsigned int *C = NULL;

    std::ifstream in("histogram.cl",std::ios_base::binary);
    in.seekg(0,std::ios_base::end);
    size_t length = in.tellg();
    in.seekg(0,std::ios_base::beg);
    std::vector<char> data(length + 1);
    in.read(&data[0], length);
    data[length] = 0;
    const char* source = &data[0];

	//std::ifstream inFile("input");
    fd = open("input",O_RDONLY);
	std::ofstream outFile("0316323.out");
    ptr = buffer;
    endd = buffer;

    unsigned int input_size;
	//inFile >> input_size;
    input_size = get_value(ptr,endd);
    size_t datasize = sizeof(unsigned int) * input_size;  
    A = (unsigned int*)malloc(datasize);  
    C = (unsigned int*)malloc(sizeof(unsigned int) * 256 * 3);  
	memset(C, 0, sizeof(unsigned int) * 256 * 3);
    for (int i = 0; i < input_size; i++)
        A[i] = get_value(ptr,endd);
		//inFile >> A[i];
    cl_int status;  
    cl_uint numPlatforms = 0;  
    status = clGetPlatformIDs(0, NULL, &numPlatforms);  
    cl_platform_id *platforms = NULL;  
    platforms=(cl_platform_id*)malloc(numPlatforms*sizeof(cl_platform_id));  
    status = clGetPlatformIDs(numPlatforms, platforms, NULL);  
    cl_uint numDevices = 0;  
    status = clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_ALL, 0, NULL, &numDevices);  
    cl_device_id *devices;  
    devices=(cl_device_id*)malloc(numDevices*sizeof(cl_device_id));  
    status = clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_ALL, numDevices, devices, NULL);  
    cl_context context;  
    context = clCreateContext(NULL, numDevices, devices, NULL, NULL, &status);  
    cl_command_queue cmdQueue;  
    cmdQueue = clCreateCommandQueue(context, devices[0], 0, &status);  
    cl_mem bufA;  
    bufA = clCreateBuffer(context, CL_MEM_READ_ONLY, datasize, NULL, &status);  
    cl_mem bufC;  
    bufC = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(unsigned int) * 256 * 3, NULL, &status);  
    status = clEnqueueWriteBuffer(cmdQueue, bufA, CL_FALSE, 0, datasize, A, 0, NULL, NULL);  
    status = clEnqueueWriteBuffer(cmdQueue, bufC, CL_FALSE, 0, sizeof(unsigned int) * 256 * 3, C, 0, NULL, NULL);  
    cl_program program = clCreateProgramWithSource(context, 1, (const char**)&source, NULL, &status);  
    status = clBuildProgram(program, numDevices, devices, NULL, NULL, NULL);  
    cl_kernel kernel;  
    kernel = clCreateKernel(program, "hist", &status);  
    status = clSetKernelArg(kernel, 0, sizeof(cl_mem), &bufA);  
    status = clSetKernelArg(kernel, 1, sizeof(cl_mem), &bufC);  
    size_t globalWorkSize[1];  
    globalWorkSize[0] = input_size;  
    status = clEnqueueNDRangeKernel(cmdQueue, kernel, 1, NULL, globalWorkSize, NULL, 0, NULL, NULL);  
    clEnqueueReadBuffer(cmdQueue, bufC, CL_TRUE, 0, sizeof(unsigned int) * 256 * 3, C, 0, NULL, NULL);  
	for (int i = 0; i < 256 * 3; i++) 
	{
		if (i % 256 == 0 && i != 0)
			outFile << std::endl;
		outFile << C[i] << ' ';
	}
    close(fd);
    clReleaseKernel(kernel);  
    clReleaseProgram(program);  
    clReleaseCommandQueue(cmdQueue);  
    clReleaseMemObject(bufA);  
    clReleaseMemObject(bufC);  
    clReleaseContext(context);  
    free(A);  
    free(C);  
    free(platforms);  
    free(devices);  
    return 0;  
}

