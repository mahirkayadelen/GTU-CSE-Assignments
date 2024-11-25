#include<stdio.h>
#include<math.h>
#include<limits.h>
int sum(int n1,int n2,int flag)
{
    int result=0;
    if(flag == 0)
    {
        if(n1%2 == 0) n1+=2;
        else n1+=1;
        while(n1<n2)
        {
            result += n1;
            if(n1+2<n2)
            {
            printf("%d + ",n1);
            }
            else{
                printf("%d = %d\n",n1,result);
            }
            n1+=2;
        }
    }
    else{
        if(n1%2 == 0) n1+=1;
        else n1+=2;
        while(n1<n2)
        {
            result += n1;
            if(n1+2<n2)
            {
            printf("%d + ",n1);
            }
            else{
                printf("%d = %d\n",n1,result);
            }
            n1+=2;
        }
    }
    return result;
}
int multi(int n1,int n2,int flag)
{
        int result=1;
    if(flag == 0)
    {
        if(n1%2 == 0) n1+=2;
        else n1+=1;
        while(n1<n2)
        {
            result *= n1;
            if(n1+2<n2)
            {
            printf("%d * ",n1);
            }
            else{
                printf("%d = %d\n",n1,result);
            }
            n1+=2;
        }
    }
    else{
        if(n1%2 == 0) n1+=1;
        else n1+=2;
        while(n1<n2)
        {
            result *= n1;
            if(n1+2<n2)
            {
            printf("%d * ",n1);
            }
            else{
                printf("%d = %d\n",n1,result);
            }
            n1+=2;
        }
    }
    return result;
}
int isprime(int a)
{
    int i;
    for(i=2;i<=sqrt(a);i++)
    {
        if(a%i == 0)    return i;
    }
    return 0;
}
void print_file()
{
    FILE *pf;
    pf = fopen("results.txt","r");
    int i;
    printf("Result :\n");
    while(fscanf(pf,"%d ",&i) != EOF)
    {
        printf("%d ",i);
    }
    printf("\n");
    fclose(pf);
}
int write_file(int a)
{
    FILE *fp;
    fp = fopen("results.txt","a+");
    fprintf(fp,"%d ",a);
    fclose(fp);
}
void sortdouble(int num1,int num2)
{
    int temp;
    if(num1>num2)
    {
        temp = num1;
        num1 = num2;
        num2 = temp;
    }
}
void sort_file()
{
    FILE* fc;
    fc = fopen("results.txt","r");
    int cond,cond_flag=0;
    cond = INT_MIN;
    int i,ctr=0,min1,min2,min3,temp;
    while(fscanf(fc,"%d",&i) != EOF)
    {
        ctr++;
    }
    fclose(fc);
    ctr/=3;
    for(;ctr>0;ctr--)
    {   
        fc = fopen("results.txt","a+");
        min1 = min2 = min3 = cond;
        while(fscanf(fc,"%d ",&i) != EOF)
        {
            if(!cond_flag)
            {
                if(i>cond)
                {
                    min1=min2=min3=i;
                    cond_flag = 1;
                }
            }
            else{
                if(i<min1 && i>cond)
                {
                    min3 = min2;
                    min2 = min1;
                    min1 = i;
                }
                else if(((min1<i && i<min2) || (min2==min3)) && i>cond)
                {
                    min3 = min2;
                    min2 = i;
                    if(min2>min3)
                    {
                        temp = min2;
                        min2 = min3;
                        min3 = temp;
                    }
                }
                else if(i<min3 && i > cond)
                {
                    min3 = i;
                }
            }
        }
        cond_flag = 0;
        cond = min3;
        fclose(fc);
        fc = fopen("temp.txt","a+");
        fprintf(fc,"%d %d %d ",min1,min2,min3);
        fclose(fc);
    }
    fc = fopen("results.txt","w"); // for deleting results contains
    fclose(fc);
    fc = fopen("temp.txt","a+");
    while(fscanf(fc,"%d ",&i) != EOF)
    {
        write_file(i);
    }
    fclose(fc);
}
int main()
{
    int operation,oper1,flag,i;
    int num1,num2;
    printf("Select operation\n1.Calculate sum/multiplication between two numbers\n2.Calculate prime numbers\n3.Show number sequence in file\n4.Sort number sequence in file\n------------------------\n");
    scanf("%d",&operation);
    switch(operation)
    {
        case 1:
        
            printf("Please enter '0'for sum, '1' for multiplication.\n");
            scanf("%d",&oper1);
            printf("Please enter '0' to work on even numbers, '1' to work on odd numbers.\n");
            scanf("%d",&flag);
            printf("Please enter two different number:\nNumber 1 :");
            scanf("%d",&num1);
            printf("Number 2:");
            scanf("%d",&num2);
            switch(oper1)
            {
                case 0:
                    write_file(sum(num1,num2,flag));
                    printf("The result is written to the result.txt file.\n");
                    break;
                case 1:
                    write_file(multi(num1,num2,flag));
                    printf("The result is written to the result.txt file.\n");
                    break;
            }
            break;
        case 2:
            printf("Please enter an integer: ");
            scanf("%d",&num1);
            for(i=2;i<num1;i++)
            {
                if(!isprime(i))  printf("%d is prime number.\n",i);
                else
                {
                    printf("%d is not a prime number, it is dividible by %d.\n",i,isprime(i));
                }
            }
            break;
        case 3:
            print_file();
            break;
        case 4:
            sort_file();
            printf("Sorting is complete.\n");
            print_file();
            break;
        default:
            printf("Invalid selection\n");
            break;
    }
    return 0;
}