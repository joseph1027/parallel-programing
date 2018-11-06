#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "mpi.h"
long long int table[100000010];
long long int prime_table[100000000];
long long int pt=1;

void make_table(long long int limit,long long int sizz)
{
    //long long int i;
    table[0] = 0;
    table[1] = 0;
    table[2] = 1;

    for(long long int i=3;i<sizz; i=i+2)
    {
        table[i] = 1;
    }
    prime_table[0] = 2;
    for(long long int i=3;i<sizz; i=i+2)
    {

        if(table[i]==1)
        {
            /*for(int j=0;j<10;j++)
            {
                printf("%lld\n",prime_table[j]);
            }*/
            long long int value = i;
            while(value<sizz)
            {

                value = value+i;
                if(value>=sizz)
                {
                    break;
                }
                table[value] = 0;
                //printf("%lld\n", value);
                /*for(int j=0;j<10;j++)
                {
                    printf("%lld ",prime_table[j]);
                }
                printf("\n");*/
            }
            /*for(int j=0;j<10;j++)
            {
                printf("%lld\n",prime_table[j]);
            }
            printf("%lld %lld\n",pt,i);*/
            prime_table[pt] = i;
            pt = pt + 1;
            /*printf("%lld %lld %lld\n",pt,i,prime_table[pt-1]);
            for(int j=0;j<10;j++)
            {
                printf("%lld\n",prime_table[j]);
            }
            char gg = getchar();*/
        }
    }
    /*for(int i=0;i<100;i++)
    {
        printf("%lld\n",prime_table[i]);
    }*/
}

int isprime(long long int n,long long int sizz,long long int sizz2) {
    long long int i,squareroot;
    if (n>=sizz)
    {
        squareroot = (long long int) sqrt(n);
        //printf("root : %lld\n",squareroot);
        //printf("pt : %lld\n",pt);
        for (i=0; i<pt; i=i+1)
        {
            if(prime_table[i]>squareroot)
            {
                break;
            }
            if ((n%(prime_table[i]))==0)
            {
                return 0;
            }
        }
        if(n>=sizz2)
        {
            for(long long int i=sizz2;i<n;i=i+2)
            {
                if(n%i==0)
                {
                    return 0;
                }
            }
            return 1;
        }
        return 1;
    }
    else
    {
        return table[n];
    }
}

long long int min(long long int a, long long int b)
{
    if(a>b)
    {
        return b;
    }
    else 
    {
        return a;
    }
}

int main(int argc, char *argv[])
{

    MPI_Init(&argc,&argv);
    int rank,size;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    long long int local_pc = 0;
    long long int local_foundone = 0;

    long long int foundone,pc=0; /* most recent prime found */
    long long int n, limit,i;
    long long int sizz;

    sscanf(argv[1],"%llu",&limit);
    if(rank==0)
        printf("Starting. Numbers to be scanned= %lld\n",limit);

    sizz = min(limit,100000000ll);
    long long int sizz2 = sizz*sizz;
    make_table(limit,sizz);
    /* Assume (2,3,5,7) are counted here */
    //printf("%llu\n",pc);
    for (n=11+rank*2; n<=limit; n=n+2*size)
    {
        if (isprime(n,sizz,sizz2))
        {
            //printf("%d\n",pc);
            local_pc = local_pc +1;
            local_foundone = n;
            //printf("local: %lld\n",local_foundone);
        }
    }
    MPI_Reduce(&local_pc,&pc,1,MPI_LONG_LONG_INT,MPI_SUM,0,MPI_COMM_WORLD);
    MPI_Reduce(&local_foundone,&foundone,1,MPI_LONG_LONG_INT,MPI_MAX,0,MPI_COMM_WORLD);
    if(rank == 0)
    {
        if(limit>10)
            printf("Done. Largest prime is %lld Total primes %lld\n",foundone,pc+4);
        else if(limit == 0 || limit == 1)
            printf("Done. Largest prime is %lld Total primes %lld\n",0,0);
        else if (limit ==2)
            printf("Done. Largest prime is %lld Total primes %lld\n",2,1);
        else if (limit ==3 || limit ==4)
            printf("Done. Largest prime is %lld Total primes %lld\n",3,2);
        else if (limit ==5 || limit == 6)
            printf("Done. Largest prime is %lld Total primes %lld\n",5,3);
        else if (limit ==7 || limit ==8 ||limit ==9 ||limit==10)
            printf("Done. Largest prime is %lld Total primes %lld\n",7,4);
        //printf("%lld\n",pc+4);
    }
    MPI_Finalize();
    return 0;
}