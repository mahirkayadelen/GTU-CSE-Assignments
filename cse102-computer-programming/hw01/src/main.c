#include<stdio.h>
#include"utils.h"

int main()
{
    int part;
    int x,y,z;
    int  passw;
    char identity_number[11];

    ft_menu:
    printf("\n\n\tWelcome the CSE 102 Homework2 MENU\nPlease select:\n1.Part 1\n2.Part 2 and 3\nChoice:");
    
    scanf("%d",&part);
    switch (part)
    {
    case 1:
        printf("Enter the first integer:");
        scanf("%d",&x);
        printf("\nEnter the second integer:");
        scanf("%d",&y);
        printf("\nEnter the divisor:");
        scanf("%d",&z);

        find_divisible(x,y,z);
        goto ft_menu;
        break;
    
    case 2 :
        printf("####ID CHECKER AND CUSTOMER CREATER####\n");
        printf("Please enter identity number:");
        scanf("%s",identity_number);
        printf("\nPlease enter password:");
        scanf("%d",&passw);
        if(validate_identity_number(identity_number))
        {
        create_customer(identity_number,passw);
        ft_login:
        printf("####LOGIN PAGE####\n");
        printf("Please enter identity number:");
        scanf("%s",identity_number);
        printf("\nPlease enter password:");
        scanf("%d",&passw);
        if(check_login(identity_number,passw))
        {
        ft_withdraw:
            if(!withdrawable_amount(180.75))
                goto ft_withdraw;
        }
        else
        {
            printf("Try again.\n");
            goto ft_login;
        }
        }
        break;
    }
    return 0;
}