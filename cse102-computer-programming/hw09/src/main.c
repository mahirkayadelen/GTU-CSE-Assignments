#include <stdlib.h>
#include <stdio.h>
#include <math.h>

union Person
{
    char name[50];
    char address[50];
    int phone;
};
union Loan
{
    float arr[3];
};
typedef struct {
   union Person customer;
   union Loan loans;
   int counter;
   int customer_id;
   float temp_loan[3];
}Bank;

Bank* bank;
char tempValue[100];

int Index=0,run=1,loan_id=0,size=10,selection=0,subrun=1,subselection=0;

void flush(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

void customeradd(Bank add_customer){

		Bank* tempbank = (Bank*) calloc(size * 2, sizeof(Bank) );
		int i =0;
		while( i<size)
        {
			tempbank[i] = bank[i];
			i++;
		}
		bank = tempbank;
		size *=2;

	bank[Index++] = add_customer;
}

void customerlist(){
	printf("\n\tList of Customers\n\n");

	for(int i=0; i<Index;i++){
			printf("Customer ID = %d \n", (bank[i].customer_id)+1 );
			printf("Customer Name = %s\n", bank[i].customer.name);
			printf("\n");
	}
}

float calculateLoan(float amount, float period, float interestRate)
{
    float loan;
    loan = amount * pow((1+interestRate),period);

    return loan;
}

void newLoan (int gecici_id)
{

                int i,flag=0,j;
                i=0;
                while( i<Index)
                {

                if(gecici_id == (bank[i].customer_id)+1)
                {

                printf("Customer Name = %s\n",bank[i].customer.name);
                flag=1;
                printf("Enter amount :");
                scanf("%f",&bank[i].loans.arr[0]);
                flush();
                printf("Enter interest rate :");
                scanf("%f",&bank[i].loans.arr[1]);
                flush();
                printf("Enter period :");
                scanf("%f",&bank[i].loans.arr[2]);
                flush();
                if(bank[i].counter == 0)
                {
                bank[i].temp_loan[bank[i].counter]=calculateLoan(bank[i].loans.arr[0],bank[i].loans.arr[2],bank[i].loans.arr[1]);
                printf("%s' Loan = > %.4f\n",bank[i].customer.name,bank[i].temp_loan[0]);
                }
                }

                i++;
                }


}

void getReport()
{
                              int gecici_id,gecici_id_loan,j;

                              printf("Enter the customer ID :");
                              scanf("%d",&gecici_id);
                              flush();
                              int i=0;
                              while(i<Index)
                              {
                              if(gecici_id == (bank[i].customer_id)+1)
                                {
                                 printf("Enter the credit ID :");
                                 scanf("%d",&gecici_id_loan);
                                 flush();
                                 if(gecici_id_loan == 0)
                                 {
                                     printf("Total Credit Value : %f\n",bank[i].temp_loan[8]);
                                     for(int j=1; j<= bank[i].loans.arr[2];j++)
                                     {
                                       printf("%d. Month Installment = %f\n",j,bank[i].temp_loan[0]/bank[i].loans.arr[2]);
                                     }
                                 }


                              }
                              i++;
                              }
}


int main ()
{
	bank = (Bank*) malloc( sizeof(Bank) * size );
	Bank bank_account;
    int gecici_id;
    FILE *fp;
    FILE *fp1;
    int flag=0;
    int j;

	while(run){
	for(int i=0;i<Index;i++)
                {
                 bank[i].counter=0;
                }
        printf("======================================\n");
        printf("Welcome to The Bank Management System\n");
        printf("======================================\n");
        printf("1.List All Customers\n");
        printf("2.Add New Customer\n");
        printf("3.New Loan Application\n");
        printf("4.Report Menu\n");
        printf("5.Exit System\n");
		scanf("%d",&selection);
		flush();
		subrun = 1;

		switch(selection){
			case 1:

                customerlist();
                selection = 0;
    			break;
    		case 2:
                fp = fopen("customer.txt","a+");
                printf("Customer Phone = ");
				scanf("%d",&(bank_account.customer.phone));
				flush();
				fprintf(fp,"%d",bank_account.customer.phone);
				printf("Customer Address = ");
				scanf("%[^\n]",(bank_account.customer.address));
				flush();
				fprintf(fp," %s",bank_account.customer.address);
                printf("Customer Name = ");
				scanf("%[^\n]",(bank_account.customer.name));
				flush();
				fprintf(fp," %s\n",bank_account.customer.name);
				printf("\n");
				bank_account.customer_id = Index;
    			customeradd(bank_account);
				fclose(fp);
				selection = 0;
    			break;
            case 3:
                printf("Enter the customer ID :");
                scanf("%d",&gecici_id);
                flush();
                newLoan(gecici_id);

                break;
            case 4:

                    printf("  ");
                    int i=0;
                    FILE *fp1=fopen("loan.txt","a+");
                 while(i<Index)
                 {
                 fprintf(fp1,"%s  %f  %f  %f\n",bank[i].customer.name,bank[i].temp_loan[0],bank[i].temp_loan[1],bank[i].temp_loan[2]);
                 i++;
                 }
                 fclose(fp1);

                    while(subrun)
                     {
					printf("\t1. Customer Details\n");
					printf("\t2. Loan Detail \n");
					printf("\t3. GO TO MAIN SUBMENU\n");
					scanf("%d",&subselection);
					flush();
					selection = 0;
                     switch(subselection){
						case 1:
                              printf("Enter the customer ID :");
                              scanf("%d",&gecici_id);
                              flush();
                              int i=0;
                              while(i<Index)
                              {
                              if(gecici_id == (bank[i].customer_id)+1)
                               {
                                  flag = 1;
                                  printf("\nCustomer ID = %d\n",(bank[i].customer_id)+1);
                                  printf("Customer Name = %s\n",bank[i].customer.name);
                                  printf("Loans = [%f + %f + %f] => 0.0000\n",bank[i].temp_loan[0],bank[i].temp_loan[1],bank[i].temp_loan[2]);
                                  printf("\n\n");
                                }
                                if (i == Index-1 && flag == 0)
                                    printf("ERROR!\n");
                                i++;
                               }

							break;
						case 2:
                               getReport();
							break;
						case 3:
                            subrun = 0;
							break;

						default:
    						printf("ERROR!\n");
    						break;
					   }

                     }
                break;
    		case 5:
    			run = 0;
    			break;
    		default:
    			printf("ERROR!\n");
				break;
		}
	}
	return 0;
}