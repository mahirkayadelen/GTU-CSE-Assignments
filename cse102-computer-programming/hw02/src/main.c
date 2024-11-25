#include <stdio.h>
#include <stdlib.h>
#include "util.h"


int main() {
    int prob;
    double pl,pw,sl,sw;

    double x1,x2,x3;
    int x4,x5;

    double slry,dist;
    int food,car,wend;
    
    printf("Welcome the CSE102 HW2\nPlease select the problem(1,2,3):"); // Asking for the problem
    scanf("%d",&prob);
    if(prob == 1)
    {
        printf("Please enter pl,pw,sl,sw in order:"); // get the input from the user for the first problem
        scanf("%lf %lf %lf %lf",&pl,&pw,&sl,&sw);
        if(dt1a(pl,pw,sl,sw) == dt1b(pl,pw,sl,sw))
        {
            if(dt1b(pl,pw,sl,sw) == 's')
                printf("Setosa\n");
            if(dt1b(pl,pw,sl,sw) == 'e')
                printf("Versicolor\n");
            if(dt1b(pl,pw,sl,sw) == 'i')
                printf("Virginica\n");
        }
        else
        {
            if(dt1a(pl,pw,sl,sw) == 's')
                printf("The first trees result is Setosa\n");
            else if(dt1a(pl,pw,sl,sw) == 'e')
                printf("The first trees result is Versicolor\n");
            else
                printf("The first trees result is Virginica\n");
            if(dt1b(pl,pw,sl,sw) == 's')
                printf("The second trees result is Setosa\n");
            else if(dt1b(pl,pw,sl,sw) == 'e')
                printf("The second trees result is Versicolor");
            else
                printf("The second trees result is Virginica\n");   
        }
    }

    else if(prob == 2)
    {
        printf("Please enter x1,x2,x3,x4,x5:");
        scanf("%lf %lf %lf %d %d",&x1,&x2,&x3,&x4,&x5);
        if(abs(dt2a(x1,x2,x3,x4,x5) - dt1b(x1,x2,x3,x4,x5)) <= CLOSE_ENOUGH)
            printf("%.1lf",(dt2a(x1,x2,x3,x4,x5) + dt1b(x1,x2,x3,x4,x5)) / 2);
        else
        {
            printf("The first trees result is %.1lf\n",dt2a(x1,x2,x3,x4,x5));
            
            if(dt2b(x1,x2,x3,x4,x5) == 0)
                printf("The second trees result is -1/7\n");
            else if(dt2b(x1,x2,x3,x4,x5) >= 0.471 && dt2b(x1,x2,x3,x4,x5) <= 0.472)
                printf("The second trees result is √2/3\n");
            else
                printf("The second trees result is %.20lf\n",dt2b(x1,x2,x3,x4,x5));
        }
    }
    else if(prob == 3)
    {
        printf("Please enter salary:");
        scanf("%lf",&slry);
        printf("\nPlease enter distance from home(km):");
        scanf("%lf",&dist);
        printf("\nPlease enter food provide (1 for yes,0 for no):");
        scanf("%d",&food);
        printf("\nPlease enter car provide(1 for yes,0 for no)");
        scanf("%d",&car);
        printf("\nWeekend work?(yes = 1, no = 0):");
        scanf("%d",&wend);
        if(dt3a(slry,dist,food,car,wend) == dt3b(slry,dist,food,car,wend) && dt3b(slry,dist,food,car,wend) == 'a')
            printf("The both trees result is ACCEPT\n");
        else if(dt3a(slry,dist,food,car,wend) == dt3b(slry,dist,food,car,wend) && dt3b(slry,dist,food,car,wend) == 'd')
            printf("The both trees result is REJECT\n");
        else
        {
            if(dt3a(slry,dist,food,car,wend) == 'a')
                printf("The first trees result is ACCEPT\n");
            else
                printf("The first trees result is REJECT\n");
            if(dt3b(slry,dist,food,car,wend) == 'a')
                printf("The second trees result is ACCEPT\n");
            else
                printf("The second trees result is REJECT\n");
        }
    }
    else
        printf("Invalid problem selection!\n");
    return 0;
}
