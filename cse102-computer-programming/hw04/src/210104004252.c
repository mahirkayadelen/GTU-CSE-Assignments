#include<stdio.h>
void get_coefficients()
{
    FILE *fp;
    fp = fopen("coefficients.txt","w");
    int a,b,c;
    printf("\nPlease enter the coefficient for the following equation: x=a*(y*y) + b*y +c\n\n");
    printf("a: ");
    scanf("%d",&a);
    printf("\nb: ");
    scanf("%d",&b);
    printf("\nc: ");
    scanf("%d",&c);
    fprintf(fp,"%d\n%d\n%d",a,b,c);
    printf("\ncoefficients.txt file has been created.\n");
    fclose(fp);
}
int draw_graph()
{
    int x,y;
    int a,b,c;
    FILE *fp;
    fp = fopen("coefficients.txt","r");
    if(fp == NULL)
    {
        printf("\nFile is not present!!\n");
        return -1;
    }
    fscanf(fp,"%d %d %d",&a,&b,&c);
    
    fclose(fp);
    for(y=16;y>=-15;y--)
    {
        for(x=-50;x<=56;x++)
        {
            if(x==0)
            {
                if(y==16) printf("^");
                else printf("|");
            }
            else if(y==0)
            {
                if(x==56) printf(">");
                else if(x==-50) printf("<");
                else printf("-");
            }
            else if(x==-2 && (y ==15 || y==10 ||  y==-5 ))
            {
                printf("\b \b");
                printf("\x1B[31m%d\x1B[0m",y);
            }
            else if(x==-2 && (y ==5 || y==0))
            {
                printf("\x1B[31m%d\x1B[0m",y);
            }
            else if(x==-2 && (y ==-10 || y==-15))
            {
                printf("\b \b\b \b");
                printf("\x1B[31m%d\x1B[0m",y);
            }
            else if(y == -1 && (x==-50 ||x==-40 ||x==-30 ||x==-20 ||x==-10 ))
            {
                
                    printf("\b \b\b \b");
                    printf("\x1B[31m%d\x1B[0m",x);
                
            }
            else if(y == -1 && (x==50 ||x==40 ||x==30 ||x==20 ||x==10 ))
            {
                    printf("\b \b");
                    if(x==10) printf("\b \b");
                    printf("\x1B[31m%d\x1B[0m",x);
            }
            else if(y == -1 && (x==-1))
            {
                    printf("\b \b\b \b");
                    printf("\x1B[31m%d\x1B[0m",x+1);
            }
            else printf(" ");
        }
        printf("\n");
    }
    printf("\033[31A\033[108D"); // 31 yukari,108 sola;
    for(y=15;y>=-15;y--)
    {
        for(x=-50;x<=56;x++)
        {
            if(x == (a*(y*y) + (b*y) + c))
            {
                printf("\033[1;34m");
				printf("#");
				printf("\033[0m");
			}
			printf("\033[1C"); // 1 saga
		}
		printf("\033[1B\033[108D"); // 1 asagi 108 sola \n gibi
    }
    return 1;
}
int print_graph()
{
    int x,y,flag=0;
    int a,b,c;
    FILE *fp;
    fp = fopen("coefficients.txt","r");
    if(fp == NULL)
    {
        printf("\nFile is not present!!\n");
        return -1;
    }
    fscanf(fp,"%d %d %d",&a,&b,&c);
    printf("\nCoefficients has been read from the coefficient file.\n");
    fclose(fp);
    fp = fopen("graph.txt","w");

    for(y=16;y>=-15;y--)
    {
        for(x=-50;x<=56;x++)
        {
            if(y <=15 && x==(a*(y*y) + b*y + c))
                fprintf(fp,"#");
            else if(x==0)
            {
                if(y==16) fprintf(fp,"^");
                else fprintf(fp,"|");
            }
            else if(y==0)
            {
                if(x==56) fprintf(fp,">");
                else if(x==-50) fprintf(fp,"<");
                else fprintf(fp,"-");
            }
            else fprintf(fp," ");
        }
        fprintf(fp,"\n");
    }
    printf("The graph of x=%d*(y*y) + %d*y + %d has been written to graph.txt file.\n",a,b,c);
    fclose(fp);
    return 1;
}
int main()
{
    int op;
    do
    {
        printf("Select an operation...\n0 -> Enter the coefficients\n1 -> Draw the graph.\n2 -> Print the graph into a .txt file.\n3 -> Exit.\n\nChoice: ");
        scanf("%d",&op);
        switch(op)
        {
            case 0:
                get_coefficients();
                break;
            case 1:
                draw_graph();
                break;
            case 2:
                print_graph();
                break;
            case 3:
                break;
            default:
                printf("\nImproper input! Please try again.\n");
                break;
        }
        
    } while (op !=3);
}