#include<stdio.h>
#include<math.h>

#define PI 3.14
enum shapes{Triangle=1,Quadrilateral,Circle,Pyramid,Cylinder};
enum calculators{Area=1,Perimeter,Volume};

int select_shape()
{
    int a,c;
    do{
    printf("Select a shape to calculate:\n----------------\n1.Triangle\n2.Quadrilateral\n3.Circle\n4.Pyramid\n5.Cylinder\n0.Exit\n-------------\nInput :");
    if(scanf("%d",&a) == 0) // if input invalid(character etc.)
    {
        a = -1;
    }
    if(c = getchar()) // for controls if inputs like 1a etc.
    {
        if(c != '\n') 
        {
            a = -1;
            while ((c = getchar()) != '\n' ) { } // for clearing buffer
        }
    }
    if(a == 0)
    {
        return 0;
    }
    else if(a == 1) return Triangle;
    else if(a == 2) return Quadrilateral;
    else if(a == 3) return Circle;
    else if(a == 4) return Pyramid;
    else if(a == 5) return Cylinder;
    else printf("ERROR ! Please enter a valid entry.\n");
    }
    while(a != 0);
}
int select_calc()
{
    int a,c;
    do{
    printf("Select calculator:\n----------------\n1.Area\n2.Perimeter\n3.Volume\n0.Exit\n-------------\nInput :");
    if(scanf("%d",&a) == 0) // if input invalid(character etc.)
    {
        a = -1;
    }
    if(c = getchar()) // for controls if inputs like 1a etc.
    {
        if(c != '\n') 
        {
            a = -1;
            while ((c = getchar()) != '\n' ) { } // for clearing buffer
        }
    }
    if(a == 0)
    {
        return 0;
    }

    else if(a == 1) return Area;
    else if(a == 2) return Perimeter;
    else if(a == 3) return Volume;
    else printf("ERROR ! Please enter a valid entry.\n");
    }
    while(a != 0);
}
float get_number()
{
    float r;
    int c;
    if(scanf("%f",&r) == 0) // if input invalid(character etc.)
    {
        r = -1;       
    }
    if(c = getchar()) // for controls if inputs like 1a etc.
    {
        if(c != '\n') 
        {
            r = -1;
            while ((c = getchar()) != '\n' ) { } // for clearing buffer
        }
    }
    if(r == -1 || r<=0 )
    {
        do
        {
            printf("\nERROR ! Please enter a valid entry.\n");
            if(scanf("%f",&r) == 0) // if input invalid(character etc.)
            {
                r = -1;
            }
            if(c = getchar()) // for controls if inputs like 1a etc.
            {
                if(c != '\n') 
                {
                    r = -1;
                    while ((c = getchar()) != '\n' ) { } // for clearing buffer
                }
            }
        } while ((r == -1  || r<=0));
    }
    return  r;
}
int calc_triangle(int a)
{
    float s1,s2,s3,s;
    float s1s2,s1s3,s2s3;
    printf("Please enter three sides of Triangle :\n");
    s1 = get_number();
    s2 = get_number();
    s3 = get_number();
    if(s1<=0 || s2<=0 || s3<=0)
    {
        do
        {
            printf("\nERROR ! Please enter a valid entry.\n");
            s1 = get_number();
            s2 = get_number();
            s3 = get_number();
        } while ((s1<=0 || s2<=0 || s3<=0));
    }
    s1s2=s1-s2;
    s1s3=s1-s3;
    s2s3=s2-s3;
    if( !(( fabs(s1s2) < s3 && (s1+s2) > s3) && (fabs(s1s3) < s2 && (s1+s3) > s2) && (fabs(s2s3) < s1 && (s2 + s3) > s1) ))
    {
        do
        {
            printf("ERROR ! Please enter a valid triangle.\n");
            s1 = get_number();
            s2 = get_number();
            s3 = get_number();
            s1s2=s1-s2;
            s1s3=s1-s3;
            s2s3=s2-s3;
        } while (!(( fabs( s1s2) < s3 && (s1+s2) > s3) && (fabs(s1s3) < s2 && (s1+s3) > s2) && (fabs(s2s3) < s1 && (s2 + s3) > s1) ));
    }
    switch(a)
    {
        case Area: //area
            s = (s1 + s2 + s3)/2;
            printf("\nArea of TRIANGLE : %.2f\n",sqrt(s*(s-s1)*(s-s2)*(s-s3)));
            break;
        case Perimeter: // perimeter
            printf("\nPerimeter of TRIANGLE : %.2f\n",(s1+s2+s3));
            break;
    }
}
int calc_quadrilateral(int a)
{
    float s1,s2,s3,s4,s;
    printf("Please enter four sides of Quadrilateral\n");
    s1 = get_number();
    s2 = get_number();
    s3 = get_number();
    s4 = get_number();
    if(s1 <=0 || s2 <=0 || s3 <=0 || s4 <=0 )
    {
        do
        {
            printf("\nERROR ! Please enter a valid entry.\n");
            s1 = get_number();
            s2 = get_number();
            s3 = get_number();
            s4 = get_number();
        } while ((s1 <=0 || s2 <=0 || s3 <=0 || s4 <=0 ));
    }
    s = (s1+s2+s3+s4)/2;
    switch(a)
    {
        case Area:
            printf("\nArea of QUADRILATERAL : %.2f\n",(sqrt((s-s1)*(s-s2)*(s-s3)*(s-s4))));
            break;
        case Perimeter:
            printf("\nPerimeter of QUADRILATERAL : %.2f\n",(s1+s2+s3+s4));
            break;
    }
}
int calc_circle(int a)
{
    float r;
    int c;
    printf("Please enter the radius of Circle:\n");
    r = get_number();
    if(r<=0 )
    {
        do
        {
            printf("\nERROR ! Please enter a valid entry.\n");
            if(scanf("%f",&r) == 0) // if input invalid(character etc.)
            {
                r = -1;
            }
            if(c = getchar()) // for controls if inputs like 1a etc.
            {
                if(c != '\n') 
                {
                    r = -1;
                    while ((c = getchar()) != '\n' ) { } // for clearing buffer
                }
            }
        } while ((r<=0 ));
    }
    switch(a)
    {
        case Area:
            printf("\nAre of CIRCLE : %.2f\n",(PI*r*r));
            break;
        case Perimeter:
            printf("\nPerimeter of CIRCLE : %.2f\n",(2*PI*r));
            break;
    }
}
int calc_pyramid(int a)
{
    float bs,sh;
    printf("Please enter the base side and height of a Pyramid :\n");
    bs = get_number();
    sh = get_number();
    if(bs<=0 || sh <= 0)
    {
        do
        {
            printf("\nERROR ! Please enter a valid entry.\n");
            bs = get_number();
            sh = get_number();
        } while ((bs<=0 || sh <= 0));
    }
    switch(a)
    {   
        case Area:
            printf("Base Surface Area of a PYRAMID : %.2f\n",(bs*bs));
            printf("\nLateral Surface Area of a PYRAMID : %.2f\n",(2*bs*sh));
            printf("\nSurface Area of a PYRAMID : %.2f",((bs*bs)+(2*bs*sh)));
            break;
        case Perimeter:
            printf("\nPerimeter of a PYRAMID : %.2f\n",4*bs);
            break;
        case Volume:
            printf("\nVolume of a PYRAMID : %.2f\n",(bs*bs*sh/3));
            break;
    }
}
int calc_cylinder(int a)
{
    float r,h;
    printf("Please enter the radius and height of a Cylinder :\n");
    r = get_number();
    h = get_number();
    if(r <= 0 || h <= 0 )
    {
        do
        {
            printf("\nERROR ! Please enter a valid entry.\n");
            r = get_number();
            h = get_number();
        } while ((r <= 0 || h <= 0 ));
    }
    switch(a)
    {
        case Area:
            printf("Base Surface Area of a CYLINDER : %.2f\n",(PI*r*r));
            printf("\nLateral Surface Area of a CYLINDER : %.2f\n",(2*PI*r*h));
            printf("\nSurface Area of a CYLINDER : %.2f",(2*PI*r*(r+h)));
            break;
        case Perimeter:
            printf("Base Surface Perimeter of a CYLINDER : %.2f\n",(2*PI*r));
            break;
        case Volume:
            printf("\n Volume of a CYLINDER : %.2f\n",(PI*r*r*h));
            break;
    }
}
int calculate( int a(),int b())
{
    int select,calculate,result;
    select = a();
    if(select == 0){
        printf("\nExiting....\n");
        return 0;
    }

    calculate = b();
    if(calculate == 0)
    {
        printf("\nExiting....\n");
        return 0;
    }
    switch(select)
    {
        case Triangle: //Triangle
            switch(calculate) //calc
            {
                case Area: // area calculate
                    calc_triangle(Area);
                    break;    
                case Perimeter:
                    calc_triangle(Perimeter);
                    break;
                case Volume:
                    printf("\nERROR ! You cannot calculate the volume of a triangle. Please try again.\n\n");
                    return -1;
                    break;
            }
        break;
        case Quadrilateral: // Quadrilateral
            switch(calculate) // calc
            {
                case Area: //area calculate
                    calc_quadrilateral(Area);
                    break;
                case Perimeter:
                    calc_quadrilateral(Perimeter);
                    break;
                case Volume:
                    printf("\nERROR ! You cannot calculate the volume of quadrilateral. Please try again.\n\n");
                    return -1;
                    break;
            }
        break;
        case Circle:
            switch(calculate)
            {
                case Area:
                    calc_circle(Area);
                    break;
                case Perimeter:
                    calc_circle(Perimeter);
                    break;
                case Volume:
                    printf("\nERROR ! You cannot calculate the volume of circle. Please try again.\n\n");
                    return -1;
                    break;
            }
        break;
        case Pyramid:
            switch(calculate)
            {
                case Area:
                    calc_pyramid(Area);
                    break;
                case Perimeter:
                    calc_pyramid(Perimeter);
                    break;
                case Volume:
                    calc_pyramid(Volume);
                    break;
            }
        break;
        case Cylinder:
            switch(calculate)
            {
                case Area:
                    calc_cylinder(Area);
                    break;
                case Perimeter:
                    calc_cylinder(Perimeter);
                    break;
                case Volume:
                    calc_cylinder(Volume);
                    break;
            }
        break;
    }
}
int main()
{
    int a;
    printf("Welcome the geometric calculator!\n\n");
    do{
    a = calculate(select_shape,select_calc);
    }
    while(a == -1);
}