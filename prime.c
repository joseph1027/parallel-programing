#include <stdio.h>
#include <stdlib.h>
#include <math.h>
long long int table[1000000];
long long int prime_table[1000000];
long long int pt=1;

void make_table(long long int limit)
{
    //long long int i;
    table[0] = 0;
    table[1] = 0;
    table[2] = 1;
    for(long long int i=3;i<1000000; i=i+2)
    {
        table[i] = 1;
    }
    prime_table[0] = 2;
    for(long long int i=3;i<1000000; i=i+2)
    {

        if(table[i]==1)
        {
            /*for(int j=0;j<10;j++)
            {
                printf("%lld\n",prime_table[j]);
            }*/
            long long int value = i;
            while(value<1000000)
            {

                value = value+i;
                if(value>=1000000)
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

int isprime(long long int n) {
    long long int i,squareroot;
    if (n>=1000000)
    {
        squareroot = (long long int) sqrt(n);
        //printf("root : %lld\n",squareroot);
        //printf("pt : %lld\n",pt);
        for (i=0; i<pt; i=i+1)
        {
            if ((n%(prime_table[i]))==0)
            {
                return 0;
            }
        }
        //printf("YO!\n");
        for(i=100;i<=squareroot;i=i+2)
        {
            if ((n%i)==0)
            return 0;
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

    scanf("%llu",&limit);
    printf("Starting. Numbers to be scanned= %lld\n",limit);
    make_table(limit);
    /* Assume (2,3,5,7) are counted here */
    //printf("%llu\n",pc);
    for (n=11; n<=limit; n=n+2)
    {
        if (isprime(n))
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