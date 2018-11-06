#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAXPOINTS 1000000
#define MAXSTEPS 1000000
#define MINPOINTS 20
#define PI 3.14159265

void check_param(void);
__global__ void init_line(float*, float*, int);
__global__ void update (float*, float*, int, int);
void printfinal (void);

int nsteps,tpoints,rcode;               
int alloc_points;
float* values,*oldval,*newval;

/**********************************************************************
 *	Checks input values from parameters
 *********************************************************************/
void check_param(void)
{
   char tchar[20];

   /* check number of points, number of iterations */
   while ((tpoints < MINPOINTS) || (tpoints > MAXPOINTS)) {
      printf("Enter number of points along vibrating string [%d-%d]: "
           ,MINPOINTS, MAXPOINTS);
      scanf("%s", tchar);
      tpoints = atoi(tchar);
      if ((tpoints < MINPOINTS) || (tpoints > MAXPOINTS))
         printf("Invalid. Please enter value between %d and %d\n", 
                 MINPOINTS, MAXPOINTS);
   }
   while ((nsteps < 1) || (nsteps > MAXSTEPS)) {
      printf("Enter number of time steps [1-%d]: ", MAXSTEPS);
      scanf("%s", tchar);
      nsteps = atoi(tchar);
      if ((nsteps < 1) || (nsteps > MAXSTEPS))
         printf("Invalid. Please enter value between 1 and %d\n", MAXSTEPS);
   }

   printf("Using points = %d, steps = %d\n", tpoints, nsteps);

}

/**********************************************************************
 *     Initialize points on line
 *********************************************************************/
__global__ void init_line(float* _oldval,float* _newval,int _tpoints)
{
   float x;
   
   int i = blockIdx.x*blockDim.x+threadIdx.x;
   if(i<_tpoints)
   {
      x = (float)i/(_tpoints - 1);
      _newval[i] = __sinf(6.2831853 * x);
      _oldval[i] = _newval[i];
   }
}

__global__ void update(float* _oldval,float* _newval,int _tpoints,int _nsteps)
{
   //int i, j;

   int i = blockIdx.x*blockDim.x+threadIdx.x;
   if(i<_tpoints)
   {
      float local_oldval = _oldval[i];
      float local_newval = _newval[i];
      float local_nextval;
      
      for(int j=0;j<_nsteps;j++)
      {
         if( (i==0) || (i==_tpoints-1))
         {
            local_nextval = 0;
         }
         else 
         {
            local_nextval = 1.82*local_newval - local_oldval;
         }
         local_oldval = local_newval;
         local_newval = local_nextval;
      }
      _newval[i] = local_newval;
   }
}

/**********************************************************************
 *     Print final results
 *********************************************************************/
void printfinal()
{
   int i;

   for (i = 0; i < tpoints; i++) {
      printf("%6.4f ", values[i]);
      if ((i+1)%10 == 0)
         printf("\n");
   }
}

/**********************************************************************
 *	Main program
 *********************************************************************/
int main(int argc, char *argv[])
{
	sscanf(argv[1],"%d",&tpoints);
	sscanf(argv[2],"%d",&nsteps);
	check_param();

   alloc_points = tpoints + 255;
   values = (float*) malloc(alloc_points * sizeof(float));
   if(!values)
   {
      exit(EXIT_FAILURE);
   }

   cudaMalloc((void**) &oldval , alloc_points*sizeof(float));
   cudaMalloc((void**) &newval , alloc_points*sizeof(float));

   dim3 threadsPerBlock(256);
   dim3 numOfBlocks(alloc_points/256);



	printf("Initializing points on the line...\n");
	init_line<<<numOfBlocks,threadsPerBlock>>>(oldval,newval,tpoints);

	printf("Updating all points for all time steps...\n");
	update<<<numOfBlocks,threadsPerBlock>>>(oldval,newval,tpoints,nsteps);
	printf("Printing final results...\n");
   cudaMemcpy(values, newval, alloc_points * sizeof(float), cudaMemcpyDeviceToHost);
	printfinal();
	printf("\nDone.\n\n");
	
	return 0;
}
