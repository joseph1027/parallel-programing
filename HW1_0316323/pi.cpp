#include<stdlib.h>
#include<pthread.h>
#include<iostream>
#include<string>
#include<time.h>

using namespace std;

unsigned long long int square;
long long int* in_circle;
struct in_data{
    long long int id;
    long long int tossess;
};

void* random_judge(void* data)
{
    //unsigned long long int square=(RAND_MAX)*(long long)(RAND_MAX);

    int id = ((in_data*)data)->id; 
    long long int tossess = ((in_data*)data)->tossess;
    long long int count = 0;
    unsigned int seed = time(NULL);
    unsigned long long int x;
    unsigned long long int y;
    //cout<<"tosses"<<tossess<<endl;
    for(long long int i = 0; i<tossess ;i++)
    {
        x=rand_r(&seed);
        y=rand_r(&seed);
        if(x*x+y*y<=square)
        {
            count++;
        }
    }
    in_circle[id] = count; 
    return NULL;
}

int main(int argc, char** argv)
{
    if(argc!= 3)
    {
        return -1;
    }
    square = (RAND_MAX)*(long long)(RAND_MAX);
    //seed = time(NULL);
    //clock_t start,end;
    srand(time(NULL));
    long long int number_of_process = stoll(argv[1]);
    long long int number_of_tosses = stoll(argv[2]);
    //cout<<"!!!"<<argv[1]<<endl;
    long long int number_in_circle = 0;
    long long int tosses_per_thread = number_of_tosses/number_of_process;
    //cout<<"per_thread"<<tosses_per_thread<<endl;
    
    in_circle = new long long int[number_of_process];
    in_data* data = new in_data[number_of_process];
    pthread_t* threads =  new pthread_t[number_of_process];
    //start = clock();
    for(long long int i = 0; i< number_of_process ;i++)
    {
        data[i].id = i;
        data[i].tossess = tosses_per_thread;
        pthread_create(&threads[i],NULL,&random_judge,&data[i]);
    }
    
    for(long long int i = 0; i<number_of_process;i++)
    {
        pthread_join(threads[i],NULL);
        number_in_circle += in_circle[i];
    }
    //end = clock();
    //long double diff = end - start;
    //long double run = diff/(CLOCKS_PER_SEC);
    //cout<<"timediff(ms):"<<run<<endl;
    //cout<<"timediff(sec):"<<timediff(end)
    cout<<4*number_in_circle/(long double)number_of_tosses<<endl;
    
    
}
