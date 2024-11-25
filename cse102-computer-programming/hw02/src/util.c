#include <stdio.h>
#include "util.h"
#include <math.h>

char    dt1a(double pl,double pw,double sl,double sw)
{
    char r;
    if(pl<2.45)
        r = 's';
    else
    {
        if(pw<1.75)
        {
            if(pl<4.95)
            {
                if(pw<1.65)
                    r = 'e';
                else
                    r = 'i';
            }
            else
                r = 'i';
        }
        else
            r = 'i';
    }

    return r;
}

char    dt1b(double pl, double pw, double sl, double sw)
{
    char r;
    if(pl<2.55){
        r ='s';
    }
    else
    {
        if(pw<1.69)
        {
            if(pl<4.85)
            {
                r = 'e';
            }
            else
                r = 'i';
        }
        else
            r = 'i';
    }
    return r;
}

double dt2a(double x1,double x2,double x3,int x4,int x5)
{
    double r;
    if(x1<31.5)
    {
        if(x2>-2.5)
            r = 5.0;
        else
        {
            if((x2-0.1)<=x1 && x1<=(x2+0.1))
                r = 2.1;
            else
                r = -1.1;
        }
    }
    else
    {
        if(-1<=x3 && x3<=2)
            return 1.4;
        else
        {
            if(x4 && x5)
                r = -2.23;
            else
                r = 11.0;
        }
    }
    return r;
}

double dt2b(double x1,double x2,double x3,int x4,int x5)
{
    double r;
    if(12<x1 && x1<22)
    {
        if(x3>(5/3))
            r = -2.0;
        else
        {
            if((x1-0.1)<=x3 && x3<=(x1+0.1))
                r = 1.01;
            else
                r = -8;
        }
    }
    else
    {
        if(x4 && x5)
            r = -1;
        else
        {
            if(-1 <= x2 && x2 <= 2)
                r = -1/7;
            else
                r = sqrt(2)/3;
        }
    }
}

char dt3a(double slry,double dist,int food,int car, int wend)
{
    char r;
    if(slry > 10000)
    {
        if(dist < 5.5)
        {
            if(wend)
            {
                if(slry>14000)
                    r = 'a';
                else
                    r = 'd';
            }
            else
                r = 'a';
        }
        else
        {
            if(car)
            {
                if(wend)
                    r = 'd';
                else 
                    r = 'a';
            }
            else
            {
                if(slry>12000)
                    r = 'a';
                else
                    r = 'd';
            }
        }
    }
    else
    {
        if(food)
        {
            r = 'a';
        }
        else
        {
            if(slry>11000)
                r = 'a';
            else
                r = 'd';
        }
    }
    return r;
}

char dt3b(double slry,double dist,int food,int car,int wend)
{
    char r;
    if(wend)
    {
        if(slry>15000)
        {
            if(car)
                r = 'a';
            else
            {
                if(dist>10)
                    r = 'd';
                else
                {
                    if(food)
                        r = 'a';
                    else
                        r = 'd';
                }
            }
        }
        else
        {
            if(food)
            {
                if(slry>14000)
                    r = 'a';
                else
                    r = 'd';
            }
            else
                r = 'd';
        }
    }
    else
    {
        if(slry>10500)
        {
            if(dist>10)
            {
                if(slry>12000)
                    r = 'a';
                else
                    r = 'd';
            }
            else
                r = 'a';
        }
        else
            r = 'd';
    }
    return r;
}
