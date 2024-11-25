#include<stdio.h>
#include"utils.h"

int find_divisible(int x, int y, int z)
{
    int i,n;

    i = 1;
    if(z == 0)
    {
        printf("Divisor can not be zero.\n");
        return 0;
    }
    while(i<y-x)
    {
        if((x + i) % z == 0)
        {
            printf("The first integer between %d and %d divided by %d is %d\n",x,y,z,x+i);
            printf("Enter the number how many next:");
            scanf("%d",&n);
            if((x+i) + n*z < y)
            {
                if(n == 1)
                    printf("The %dnd integer between %d and %d divided by %d is %d\n",n+1,x,y,z,find_nth_divisible(n,x+i,z));
                else if(n == 2)
                    printf("The %drd integer between %d and %d divided by %d is %d\n",n+1,x,y,z,find_nth_divisible(n,x+i,z));
                else
                    printf("The %dth integer between %d and %d divided by %d is %d\n",n+1,x,y,z,find_nth_divisible(n,x+i,z));
            }
            return 1;
        }
        i++;
    }
    printf("There is not any integer between %d and %d can be divided by %d\n",x,y,z);
    return 0;
}

int find_nth_divisible(int n,int f_l,int z)
{
    f_l += n*z;
    return f_l;
}

int validate_identity_number(char identity_number [])
{
    int ctr,i;
    int odds,evens;

    odds = 0;
    evens = 0;
    ctr = 0;
    i = 0;
    if(identity_number[0] == '0')
    {
        printf("Invalid Identity number.\n");
        return 0;
    }
    while(identity_number[ctr])
    {
        if(identity_number[ctr] >= '0' && identity_number[ctr] <= '9') // controls the second condition
            ctr++;
        else
        {
            printf("Invalid Identity number.\n");
            return 0;
        }
    }
    if(ctr != 11 || identity_number[0] == '0') // controls the 1st and 3rd conditions
    {
        printf("Invalid Identity number.\n");
        return 0;
    }
    i = 1;
    while(i<=7) // get 2 4 6 8 digits sum
    {
        odds+= identity_number[i] - '0';
        i+=2;
    }
    i = 0;
    while(i<=8) // get 1 3 5 7 9 digits sum
    {
        evens += identity_number[i] - '0';
        i+=2;
    }
    if( ((evens*7) - odds ) % 10  != (identity_number[9] - '0')) // controls the 4th condition
    {
        printf("Invalid Identity number.\n");
        return 0;
    }
    odds = 0;
    for(i = 0;i <10;i++)
    {
        odds += identity_number[i] -'0';
    }
    if(odds % 10  != identity_number[10] - '0') // controls the 5th condition
    {
        printf("Invalid Identity number.\n");
        return 0;
    }
    printf("Identity number verified!\n");
    return 1;
}
int create_customer(char identity_number[],int password)
{
    FILE *ptr;
    ptr = fopen("customeraccount.txt","w");

    /*if(ptr = NULL)
    {
        printf("Can not open file");
        return 0;
    }*/
    fprintf(ptr,"%s,%d",identity_number,password);
    printf("Customer created successfuly!\n");

    fclose(ptr);
    return 1;
}
int check_login(char identity_number[], int password)
{
    FILE * ptr;
    int i;
    char    identity_num[11];
    char pass[4];
    int intpass;

    intpass = 0;
    i = 0;
    ptr = fopen("customeraccount.txt","r");
    while(i<11)
    {
        fscanf(ptr,"%c",&identity_num[i]);
        i++;
    }
    
    for(i = 0;i<=10;i++) // controls the identitynumber match
    {
        if(identity_num[i] != identity_number[i])
        {
            printf("Invalid identity number or password\n");
            return 0;
        }
        i++;
    }
    fseek(ptr,12,SEEK_SET); // for start at password
    fscanf(ptr,"%s",pass);

    for(i=0;i<=3;i++) // converts string to integer(password)
    {
        intpass += pass[i] - '0';
        if(i!=3)
            intpass *=10;
    }

    if(!(password == intpass)) // controls the password match
    {
        printf("Invalid identity number or password\n");
        return 0;
    }
    printf("Login successful\n");
    fclose(ptr);
    return 1;
}

int withdrawable_amount(float cash_amount)
{
    int wint;
    float mod,withdraw;
    
    printf("Enter your withdraw amount:");
    scanf("%f",&withdraw);
    mod = withdraw;
    while(mod >= 10.00) // Find modulus of floating point number
        mod -= 10.00;
    if(mod == 0)
    {
        printf("\nWithdraw successful!\n");
        cash_amount -= withdraw;
        return 1;
    }
    else
    {
        wint = withdraw;
        if(wint % 10 == 0)
            printf("Withdrawable amount is %d \n",wint);
        else
        {
            wint /=10;
            wint *=10;
            printf("\nWithdrawable amount is %d\n",wint);
        }
    }
    return 0;
}