#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

void rand_word(int n,char single_word[10]) // reads nth line and takes word into single_word array 
{
    FILE *fp;
    fp = fopen("wordlist.txt","r");
    
    for(int i = 0;i<n;i++)
    {
        fscanf(fp,"%s",single_word);
    }
    fclose(fp);
}

int control_word(char gameboard[15][15],int x,int y,char inp[10]) // checking the word by looking at the positions at gameboard
{
    int dx = x,dy=y;
    if(gameboard[y][x] == inp[0])
    {
        if(gameboard[y][x+1] == inp[1]) // saga
        {
            x++;
            for(int i = 2;i<strlen(inp);i++)
            {
                if(gameboard[y][++x] == inp[i]);
                else
                    return -1;
            }
            for(int i = 0;i<strlen(inp);i++) // for replacing letters with X
            {
                gameboard[dy][dx+i] = 'X';
            }
            return 1;
        }
        else if(gameboard[y][x-1] == inp[1]) // sola
        {
            x--;
            for(int i = 2;i<strlen(inp);i++)
            {
                
                if(gameboard[y][--x] == inp[i]);
                else
                    return -1;
            }
            for(int i = 0;i<strlen(inp);i++) // for replacing letters with X
            {
                gameboard[dy][dx-i] = 'X';
            }
            return 1;
        }
        else if(gameboard[y+1][x] == inp[1]) // asagi
        {
            y++;
            for(int i = 2;i<strlen(inp);i++)
            {
                if(gameboard[++y][x] == inp[i]);
                else
                    return -1;
            }
            for(int i = 0;i<strlen(inp);i++) // for replacing letters with X
            {
                gameboard[dy+i][dx] = 'X';
            }
            return 1;
        }
        else if(gameboard[y-1][x] == inp[1]) // yukari
        {
            y--;
            for(int i = 2;i<strlen(inp);i++)
            {
                if(gameboard[--y][x] == inp[i]);
                else
                    return -1;
            }
            for(int i = 0;i<strlen(inp);i++) // for replacing letters with X
            {
                gameboard[dy-i][dx] = 'X';
            }
            return 1;
        }
        else if(gameboard[y+1][x+1] == inp[1]) // sag capraz duz
        {
            x++;
            y++;
            for(int i =2;i<strlen(inp);i++)
            {
                if(gameboard[++y][++x] == inp[i]);
                else
                    return -1;
            }
            for(int i = 0;i<strlen(inp);i++) // for replacing letters with X
            {
                gameboard[dy+i][dx+i] = 'X';
            }
            return 1;
        }
        else if(gameboard[y-1][x-1] == inp[1]) // sag capraz ters
        {
            y--;
            x--;
            for(int i =2;i<strlen(inp);i++)
            {
                if(gameboard[--y][--x] == inp[i]);
                else
                    return -1;
            }
            for(int i = 0;i<strlen(inp);i++) // for replacing letters with X
            {
                gameboard[dy-i][dx-i] = 'X';
            }
            return 1;
        }

        else if(gameboard[y+1][x-1] == inp[1]) // sol capraz duz
        {
            y++;
            x--;
            for(int i =2;i<strlen(inp);i++)
            {
                if(gameboard[++y][--x] == inp[i]);
                else
                    return -1;
            }
            for(int i = 0;i<strlen(inp);i++) // for replacing letters with X
            {
                gameboard[dy+i][dx-i] = 'X';
            }
            return 1;
        }

        else if(gameboard[y-1][x+1] == inp[1]) // sol capraz ters
        {
            y--;
            x++;
            for(int i =2;i<strlen(inp);i++)
            {
                if(gameboard[--y][++x] == inp[i]);
                else
                    return -1;
            }
            for(int i = 0;i<strlen(inp);i++) // for replacing letters with X
            {
                gameboard[dy-i][dx+i] = 'X';
            }
            return 1;
        }
    }
    else
        return -1;
}

void print_board(char gameboard[15][15]) // prints the gameboard
{
    for(int i = 0;i<15;i++)
    {
        for(int j = 0;j<15;j++)
        {
            printf("%c ",gameboard[i][j]);
        }
        printf("\n");
    }
}

void write_word(char single_word[10],char gameboard[15][15]) // fills random words into the board
{
    int s;
    int x,y;
    int dx,dy;
    x = rand() % 15;
    dx = x;
    y = rand() % 15;
    
    dy = y;
    s = rand() % 8;
    if(s == 0) // saga yaz
    {
        for(int i = 0;i<strlen(single_word);i++) // Checking if there is enough space for the word if not, takes random place and direction again by recursive
        {
            if(gameboard[dy][dx] != '.' || dx>=15)
            {
                write_word(single_word,gameboard);
                return;
            }
            dx+=1;
        }
        printf("%s %d %d\n",single_word,y,x);
        for(int i = 0;i<strlen(single_word);i++) // filling word char by char
        {

            gameboard[y][x] = single_word[i];
            x++;
        }
    }

    else if(s == 1) // sola yaz
    {
        for(int i = 0;i<strlen(single_word);i++) // Checking if there is enough space for the word
        {
            if(gameboard[dy][dx] != '.' || dx>=15)
            {
                write_word(single_word,gameboard);
                return;
            }
            dx+=1;
        }
        
        for(int i = strlen(single_word)-1;i>=0;i--) // filling word char by char
        {
            gameboard[y][x] = single_word[i];
            x++;
        }
        x--;
        printf("%s %d %d\n",single_word,y,x);
    }

    else if(s == 2) // asagi yaz
    {
        for(int i = 0;i<strlen(single_word);i++) // Checking if there is enough space for the word
        {
            if(gameboard[dy][dx] != '.' || dy>=15)
            {
                write_word(single_word,gameboard);
                return;
            }
            dy+=1;
        }
        printf("%s %d %d\n",single_word,y,x);
        for(int i = 0;i<strlen(single_word);i++) // filling word char by char
        {
            gameboard[y][x] = single_word[i];
            y++;
        }
    }

    else if(s == 3) // yukari yaz
    {
        for(int i = 0;i<strlen(single_word);i++) // Checking if there is enough space for the word
        {
            if(gameboard[dy][dx] != '.' || dy>=15)
            {
                write_word(single_word,gameboard);
                return;
            }
            dy+=1;
        }
        
        for(int i = strlen(single_word)-1;i>=0;i--) // filling word char by char
        {
            gameboard[y][x] = single_word[i];
            y++;
        }
        y--;
        printf("%s %d %d\n",single_word,y,x);
    }
    
    else if(s == 4) // saga düz
    {
        for(int i = 0;i<strlen(single_word);i++) // Checking if there is enough space for the word
        {
            if(gameboard[dy][dx] != '.' || dy>=15 || dx >= 15)
            {
                write_word(single_word,gameboard);
                return;
            }
            dy+=1;
            dx+=1;
        }
    printf("%s %d %d\n",single_word,y,x);
    for(int i = 0;i<strlen(single_word);i++) // filling word char by char
        {
            gameboard[y][x] = single_word[i];
            x++;
            y++;
        }
    }

    else if(s == 5) // saga ters
    {
        for(int i = 0;i<strlen(single_word);i++) // Checking if there is enough space for the word
        {
            if(gameboard[dy][dx] != '.' || dy>=15 || dx >= 15)
            {
                write_word(single_word,gameboard);
                return;
            }
            dy+=1;
            dx+=1;
        }
        
        for(int i = strlen(single_word)-1;i>=0;i--) // filling word char by char
        {
            gameboard[y][x] = single_word[i];
            x++;
            y++;
        }
        x--;
        y--;
        printf("%s %d %d\n",single_word,y,x);
    }

    else if(s == 6) // sola duz
    {
        for(int i = 0;i<strlen(single_word);i++) // Checking if there is enough space for the word
        {
            if(gameboard[dy][dx] != '.' || dy>=15 || dx < 0)
            {
                write_word(single_word,gameboard);
                return;
            }
            dy+=1;
            dx-=1;
        }
        printf("%s %d %d\n",single_word,y,x);
        for(int i = 0;i<strlen(single_word);i++) // filling word char by char
        {
            gameboard[y][x] = single_word[i];
            x--;
            y++;
        }
    }

    else if(s == 7) // sola ters
    {
        for(int i = 0;i<strlen(single_word);i++) // Checking if there is enough space for the word
        {
            if(gameboard[dy][dx] != '.' || dy>=15 || dx < 0)
            {
                write_word(single_word,gameboard);
                return;
            }
            dy+=1;
            dx-=1;
        }
        
        for(int i = strlen(single_word)-1;i>=0;i--) // filling word char by char
        {
            gameboard[y][x] = single_word[i];
            x--;
            y++;
        }
        x++;
        y--;
        printf("%s %d %d\n",single_word,y,x);
    }
}

int main()
{
    int n,x,y; // n takes the random line for word in text file and x,y coordinates of word
    int left =3,tpoints=0; // left right player,total points of player
    char inp[10]; // input word for check
    char gameboard[15][15];
    int arr[8] = {};
    int j; 
    char single_word[10]; // includes random word for filling gameboard
    srand(time(NULL));
    for(int i = 0;i<15;i++) // fill gameboard fully dots
    {
        for(int j = 0;j<15;j++)
        {
            gameboard[i][j] = '.';
        }
    }

    for(int i = 0; i < 7; i++) // each loop for different word totally 7 word
    {
        j = 0;
        n = rand() % 50; // nth line(word)
            do
            {
                if(n == arr[j])
                    {
                        n = rand() % 50; // nth line(word)
                        j = 0;
                        continue;
                    }
                j++;
            } while (j <= i);
        arr[i] = n;
        rand_word(n,single_word);
        //printf("%s\n",single_word);
        write_word(single_word,gameboard); // writes each word randomly to the gameboard
    }

    for(int i = 0;i<15;i++) // fills the dots(gaps) with random letters
    {
        for(int j = 0;j<15;j++)
        {
            if(gameboard[i][j] == '.')
                gameboard[i][j] = 97 + (rand() % 26);
            
        }
    }
    print_board(gameboard);
    do
    {
        printf("\nEnter word and coordinates:");
        scanf("%s",inp);
        if((strcmp(":q",inp)) == 0) // if input string is ":q" then break.
        {
            printf("\nExiting..\n");
            break;
        }
        scanf("%d %d",&y,&x);
        if(control_word(gameboard,x,y,inp) == 1)
        {
            tpoints +=2;
            print_board(gameboard);
            printf("Founded! You got 2 points. Your total points : %d\n",tpoints);
        }
        else
        {
            left-=1;
            print_board(gameboard);
            printf("\nWrong choice! You have only %d lefts.\n",left);
        }
    } while (left >0 && tpoints < 14);
    if(tpoints == 14)
        printf("\nCongratulations You WON!!\n");
    else if(left == 0)
        printf("\nYou LOST!\n");
}