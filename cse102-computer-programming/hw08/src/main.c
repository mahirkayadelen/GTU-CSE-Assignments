#include<stdio.h>
#include<stdlib.h>
#include"util.h"

int main()
{
    int first,size;
    printf("Please enter the sequence length: ");
    scanf("%d",&size);
    printf("Please enter the first element: ");
    scanf("%d",&first);

    int *loop = malloc(sizeof(int)*size/2);
    int looplen = size/2;

    check_loop_iterative(generate_sequence,first,size,loop,&looplen);

    int *histogram = calloc(9,sizeof(int));
    int digit = 0;

    hist_of_firstdigits(generate_sequence,first,size,histogram,digit);
    printf("\nHistogram of the sequence : {");

    for (int i = 0; i < 9; i++)     //PRint histogram
    {
        if(i == 8)
            printf("%d}",histogram[i]);
        else
            printf("%d, ",histogram[i]);
    }
    printf("\n");
}