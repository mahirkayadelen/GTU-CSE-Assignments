#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void printMap(int p1c,int p1r,int p2c,int p2r,char gameboard[][30])
{    
    for(int i=0;i<15;i++) // takes row of the gameboard 
    {
        for(int j=0;j<30;j++) // takes column of the gameboard
        {
            if(j == p1c && i == p1r)
                printf("\033[0;33m%c\033[0m",gameboard[i][j]);
            else if(j == p2c && i == p2r)
                printf("\033[0;34m%c\033[0m",gameboard[i][j]);
            else if((i == 1 && j == 14) ||(i == 7 && j == 28) ||(i == 13 && j == 14) ||(i == 3 && j == 10) ||(i == 3 && j == 18) ||(i == 5 && j == 26) ||(i == 10 && j == 26) ||(i == 11 && j == 10) ||(i == 11 && j == 18))
                printf("\33[0;31m%c\033[0m",gameboard[i][j]);
            else if((i == 2 && j == 1) ||(i == 4 && j == 3)) 
                printf("\033[0;32m%c\033[0m",gameboard[i][j]);
            else if(i ==0 || i ==14 || (i == 2 && (j>1 && j<28)) || (i == 12 && (j>1 && j<28)) || (i == 4 && (j>3 && j<26)) || (i == 10 && (j>3 && j<26)) ) 
                printf("%c",gameboard[i][j]);
            else if((j == 0 && (i > 0 && i< 14 )) || (j == 2 && (i>2 && i<12)) || (j == 27 && (i>2 && i<12)) || (j ==4 && (i>4 && i<10)) || (j ==25 && (i>4 && i<10))|| (j == 29 && (i>0 && i<29)))
                printf("%c",gameboard[i][j]);
            else 
                printf("%c",gameboard[i][j]);
        }
        printf("\n");
    }  
}
int dice() // gives random int within range 1 and 6
{
    int a;
    a = (rand() % 6) + 1;
    return a;
}
int startgame() // returns the # of the player who starts to the game
{
    int p1,p2;

    printf("\033[0;33mPlayer 1... press ENTER to dice\033[0m");
    getchar();
    p1 = dice();
    printf("\033[0;33mDICE: %d\033[0m",p1);
    printf("\n\033[0;34mPlayer 2... press ENTER to dice\033[0m");
    getchar();
    p2 = dice();
    printf("\033[0;34mDICE: %d\n\033[0m",p2);
    

    if(p1 > p2)
        return 1;
    else if(p2 > p1)
        return 2;
    else
        return 0;
}
void game()
{
    int next,played = 0; // next :includes dice value, played: controls print condition
    int p1saga=1,p1sola=0,p1asagi=0,p1yukari=0; // controls improve which side for P1
    int p2saga=1,p2sola=0,p2asagi=0,p2yukari=0; // controls improve which side for P2   
    int p1c=1,p1r=1,p2c=3,p2r=3; // takes first place of players
    int dt; // dice turn
    int remain=0;
    char gameboard[15][30];

    for(int i=0;i<15;i++) // fill gameboard to array 
    {
        for(int j=0;j<30;j++)
        {
            if(j == p1c && i == p1r)
                gameboard[i][j] = '1';
            else if(j == p2c && i == p2r)
                gameboard[i][j] = '2';
            else if((i == 1 && j == 14) ||(i == 7 && j == 28) ||(i == 13 && j == 14) ||(i == 3 && j == 10) ||(i == 3 && j == 18) ||(i == 5 && j == 26) ||(i == 10 && j == 26) ||(i == 11 && j == 10) ||(i == 11 && j == 18))
                gameboard[i][j] = 'X';
            else if((i == 2 && j == 1) ||(i == 4 && j == 3)) 
                gameboard[i][j] = '-';
            else if(i ==0 || i ==14 || (i == 2 && (j>1 && j<28)) || (i == 12 && (j>1 && j<28)) || (i == 4 && (j>3 && j<26)) || (i == 10 && (j>3 && j<26)) ) 
                gameboard[i][j] = '.';
            else if((j == 0 && (i > 0 && i< 14 )) || (j == 2 && (i>2 && i<12)) || (j == 27 && (i>2 && i<12)) || (j ==4 && (i>4 && i<10)) || (j ==25 && (i>4 && i<10))|| (j == 29 && (i>0 && i<29)))
                gameboard[i][j] = ':';
            else 
                gameboard[i][j] = ' ';
        }
    }

    printMap(p1c,p1r,p2c,p2r,gameboard);
    printf("To start to game, players should dice and decide who is going to start first according it...\n");

    do 
    {
        dt = startgame();
        if(dt == 0)
            printf("Same dice value... Please try again.\n");
        else if(dt == 1)
            printf("\n ***Player 1 will start the game...***\n");
        else 
            printf("\n ***Player 2 will start the game...***\n");
    } while (dt == 0);

    while( !(p1c == 1 && p1r == 2) && !(p2c == 3 && p2r == 4) ) // game continue till  reach endpoints
    {

        if(p1c ==28 && p1r == 1) // asagi ilerle p1
        {
            p1asagi=1;
            p1sola=0;
            p1saga=0;
            p1yukari=0;
        }
        else if( p1c == 28 && p1r == 13) // sola ilerle p1
        {
            p1asagi=0;
            p1sola=1;
            p1saga=0;
            p1yukari=0;
        }
        else if(p1c == 1 && p1r == 13) // yukari ilerle p1
        {
            p1asagi=0;
            p1sola=0;
            p1saga=0;
            p1yukari=1;
        }
        
        if(p2c == 26 && p2r == 3) // asagi ilerle p2
        {
            p2asagi =1;
            p2sola = 0;
            p2saga = 0;
            p2yukari = 0;
        }
        else if(p2c  == 26 && p2r == 11)// sola ilerle p2
        {
            p2asagi =0;
            p2sola = 1;
            p2saga = 0;
            p2yukari = 0;
        }
        else if(p2c == 3 && p2r == 11) // yukari ilerle p2
        {
            p2asagi =0;
            p2sola = 0;
            p2saga = 0;
            p2yukari = 1;
        }

        if(dt == 1)
        {
            if(p1saga)
            {
                printf("\033[0;33mPlayer 1... press ENTER to dice\033[0m");
                getchar();
                next = dice();
                printf("\033[0;33mDICE: %d\n\033[0m",next);
                p1c += next;
                if(p1c >28)
                {
                    p1r+= p1c -28; // adds remain part 
                    p1c =28;
                    p1asagi=1;
                    p1sola=0;
                    p1saga=0;
                    p1yukari=0;
                }
                if( (p1c == 14) && (p1r == 1) ) 
                {
                    p1c -=2;
                    printf("\033[0;33mPenalty for Player 1...\n\033[0m");
                }
            }
            else if(p1asagi)
            {
                printf("\033[0;33mPlayer 1... press ENTER to dice\033[0m");
                getchar();
                next = dice();
                printf("\033[0;33mDICE: %d\n\033[0m",next);
                p1r += next;
                if(p1r >13)
                {
                    p1c-= p1r -13;
                    p1r =13;
                    p1asagi=0;
                    p1sola=1;
                    p1saga=0;
                    p1yukari=0;
                }

                if( (p1c == 28) && (p1r == 7) ) 
                {
                    p1r-=2;
                    printf("\033[0;33mPenalty for Player 1...\n\033[0m");
                }
            }
            else if(p1sola)
            {
                printf("\033[0;33mPlayer 1... press ENTER to dice\033[0m");
                getchar();
                next = dice();
                printf("\033[0;33mDICE: %d\n\033[0m",next);
                p1c -= next;
                if(p1c <1)
                {
                    p1r -= 1-p1c;
                    p1c =1;
                    p1asagi=0;
                    p1sola=0;
                    p1saga=0;
                    p1yukari=1;
                }

                if((p1c == 14 ) && (p1r == 13 ))
                { 
                    p1c+= 2;
                    printf("\033[0;33mPenalty for Player 1...\n\033[0m");
                }
            }
            else if(p1yukari)
            {
                printf("\033[0;33mPlayer 1... press ENTER to dice\033[0m");
                getchar();
                next = dice();
                printf("\033[0;33mDICE: %d\n\033[0m",next);
                p1r -= next;
                if(p1r <2)
                {
                    p1r =2;
                }
            }
            dt +=1;
            played +=1;
        }
        else if(dt == 2)
        {
            if(p2saga)
            {
                printf("\033[0;34mPlayer 2... press ENTER to dice\033[0m");
                getchar();
                next = dice();
                printf("\033[0;34mDICE : %d\n\033[0m",next);
                p2c += next;
                if(p2c >26)
                {
                    p2r+= p2c -26;
                    p2c =26;
                    p2asagi =1;
                    p2sola = 0;
                    p2saga = 0;
                    p2yukari = 0;
                }
                if(((p2c == 10 ) && (p2r == 3 )) || ((p2c == 18 ) && (p2r == 3 ) )) 
                {
                    p2c -=2;
                    printf("\033[0;34mPenalty for player 2...\n\033[0m");
                }
            }
            else if(p2asagi)
            {
                printf("\033[0;34mPlayer 2... press ENTER to dice\033[0m");
                getchar();
                next = dice();
                printf("\033[0;34mDICE : %d\n\033[0m",next);
                p2r += next;
                if(p2r >11)
                {
                    p2c -= p2r-11;
                    p2r =11;
                    p2asagi =0;
                    p2sola = 1;
                    p2saga = 0;
                    p2yukari = 0;
                }

                if(((p2c == 26 ) && (p2r == 5 )) || ((p2c == 26 ) && (p2r == 10 ) )) 
                {
                    p2r -=2;
                    printf("\033[0;34mPenalty for player 2...\n\033[0m");
                }
            }
            else if(p2sola)
            {
                printf("\033[0;34mPlayer 2... press ENTER to dice\033[0m");
                getchar();
                next = dice();
                printf("\033[0;34mDICE : %d\n\033[0m",next);
                p2c -= next;
                if(p2c < 3)
                {
                    p2r -= 3-p2c;
                    p2c =3;
                    p2asagi =0;
                    p2sola = 0;
                    p2saga = 0;
                    p2yukari = 1;
                }

                if(((p2c == 10 ) && (p2r == 11 )) || ((p2c == 18 ) && (p2r == 11 ) )) 
                {
                    p2c -=2;
                    printf("\033[0;34mPenalty for player 2...\n\033[0m");
                }
            }
            else if(p2yukari)
            {
                printf("\033[0;34mPlayer 2... press ENTER to dice\033[0m");
                getchar();
                next = dice();
                printf("\033[0;34mDICE : %d\n\033[0m",next);
                p2r -= next;
                if(p2r <4)
                {
                    p2r =4;
                }
            }

            played +=1;
            dt -=1;
        }

        if(p1c == 1 && p1r ==2) // if P1 on the finish point
        {
            printf("\n\n\n\033[0;33m*** PLAYER 1 WON THE GAME***\n\033[0m\n");
        }

        if(p2c == 3 && p2r == 4) // if P1 on the finish point
        {
            printf("\n\n\n\033[0;34mPLAYER 2 WON THE GAME***\n\033[0m\n");
        }

        for(int i=0;i<15;i++) // update gameboard with new positions
        {
            for(int j=0;j<30;j++)
            {
                if(j == p1c && i == p1r)
                    gameboard[i][j] = '1';
                else if(j == p2c && i == p2r)
                    gameboard[i][j] = '2';
                else if((i == 1 && j == 14) ||(i == 7 && j == 28) ||(i == 13 && j == 14) ||(i == 3 && j == 10) ||(i == 3 && j == 18) ||(i == 5 && j == 26) ||(i == 10 && j == 26) ||(i == 11 && j == 10) ||(i == 11 && j == 18))
                    gameboard[i][j] = 'X';
                else if((i == 2 && j == 1) ||(i == 4 && j == 3)) 
                    gameboard[i][j] = '-';
                else if(i ==0 || i ==14 || (i == 2 && (j>1 && j<28)) || (i == 12 && (j>1 && j<28)) || (i == 4 && (j>3 && j<26)) || (i == 10 && (j>3 && j<26)) ) 
                    gameboard[i][j] = '.';
                else if((j == 0 && (i > 0 && i< 14 )) || (j == 2 && (i>2 && i<12)) || (j == 27 && (i>2 && i<12)) || (j ==4 && (i>4 && i<10)) || (j ==25 && (i>4 && i<10))|| (j == 29 && (i>0 && i<29)))
                    gameboard[i][j] = ':';
                else 
                    gameboard[i][j] = ' ';
        }
        }

        if(played ==2 || (p1c == 1 && p1r ==2) || (p2c == 3 && p2r == 4)) // prints map per 2 dice | finish points
        {
            printMap(p1c,p1r,p2c,p2r,gameboard);
            played =0;
        }
    }
}
int main()
{
    int start,result;
    srand(time(NULL));
    int p1c=1,p1r=1,p2c=3,p2r=3;
    game();
}