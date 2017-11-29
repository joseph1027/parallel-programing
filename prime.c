#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
long long int table[100000000];
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

int isprime(long long int n,long long int sizz) {
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
        if(n>=sizz*sizz)
        {
            for(long long int i=sizz*sizz;i<n;i=i+2)
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

int main(int argc, char *argv[])
{
    long long int foundone,pc=0; /* most recent prime found */
    long long int n, limit,i;
    long long int sizz;

    sscanf(argv[1],"%llu",&limit);
    printf("Starting. Numbers to be scanned= %lld\n",limit);

    if(limit>=50000000)
    {
        sizz = 100000000;
    }
    else if(limit<50000000 && limit>=5000000)
    {
        sizz=10000000;
    }
    else
    {
        sizz = 1000000;
    }
    make_table(limit,sizz);
    /* Assume (2,3,5,7) are counted here */
    //printf("%llu\n",pc);
    for (n=11; n<=limit; n=n+2)
    {
        if (isprime(n,sizz))
        {
            //printf("%d\n",pc);
            pc = pc +1;
            foundone = n;
        }
    }
    printf("Done. Largest prime is %lld Total primes %lld\n",foundone,pc+4);
    //printf("%lld\n",pc+4);
    return 0;
}