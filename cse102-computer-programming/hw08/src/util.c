#include"util.h"
#include<stdio.h>
#include<stdlib.h>

int digit_find(int num)
{
    int dnum = num;
    int b=0;
    for(;dnum>0;dnum/=10)
        b++;
    for(int i = 1;i<b;i++)
    {
        num/=10;
    }
    return num;
}

void generate_sequence(int xs, int currentlen,int seqlen, int *seq)
{
    seq[currentlen] = xs;
    if(currentlen<seqlen && xs%2==0)
        generate_sequence(xs/2,currentlen+1,seqlen,seq);
    else if(currentlen<seqlen) // odd number
        generate_sequence((3*xs)+1,currentlen+1,seqlen,seq);
}

void check_loop_iterative(void (*f)(int, int ,int, int*), int xs, int seqlen, int *loop, int *looplen)
{
    int *ptr = malloc(sizeof(int)*seqlen);
    f(xs,0,seqlen, ptr);
    int ls, le;

    if (*looplen == seqlen/2)
    {
        for (int i = 0; i < seqlen; i++)
            printf("%d, ",ptr[i]);
    }

    if (*looplen >= 2){
        printf("\nChecking if there is a loop of length %d...",*looplen);
        int flag = has_loop(ptr,seqlen, *looplen,&ls,&le);

        if (flag == 0){
            (*looplen)--;
            check_loop_iterative(f,xs,seqlen,loop,looplen);
        }

        else if (flag == 1){
            printf("\n\nLOOP FOUND AT INDEX %d(first digit), %d(last digit)\n",ls,le);
        }
    }

    else{
        *looplen = 0;
        free(loop);
    }
}

int has_loop(int *arr, int n, int looplen, int *ls, int *le)
{
    int sayac = 0, i=0,j=0;
    for(;i<n;i++)
    {
        for(j=i;j<i+looplen;j++)
        {
            if(arr[j] ==arr[j+looplen])
                sayac++;
        }
        if(sayac == looplen)
        {
            *ls = j - looplen;
            *le = j-1;
            return 1;
        }
        sayac = 0;
    }
    return 0;
}

void hist_of_firstdigits(void (*f)(int, int ,int, int*), int xs, int seqlen, int *h, int digit)
{
    if (digit != seqlen)
    {
    int *ptr = malloc(sizeof(int)*seqlen);
    f(xs,0,seqlen, ptr);
    int first_digit = digit_find(ptr[digit]);
    h[first_digit-1] +=1;
    digit += 1;
    hist_of_firstdigits(f,xs,seqlen,h,digit);
    }
}