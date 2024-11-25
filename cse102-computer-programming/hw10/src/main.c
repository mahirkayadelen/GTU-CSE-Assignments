#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define STACK_BLOCK_SIZE 10 // stacks first size

typedef struct{
    int *array;
    int currentsize;
    int maxsize;

}stack;
int push(stack *s,int d)
{
    if(s->currentsize == s->maxsize) // if the current size of the array exceeds the space we have allocated, we will increase the space
    {
        int *temp;
        temp = (int *)malloc(sizeof(int)*(s->maxsize));
        s->maxsize+=1;
        for(int i = 0;i<s->maxsize-1;i++) 
        {
              temp[i]=s->array[i];
        }
        free(s->array);
        s->array = (int*)malloc(sizeof(int)*s->maxsize);
        for(int i = 0;i<s->maxsize-1;i++)
        {
            s->array[i] = temp[i];
        }
        free(temp);
    }
    s->array[s->currentsize] = d;
    s->currentsize+=1;
    return d; // returns pushed value

} // the stack array will grow STACK_BLOCK_SIZE entries at a time

int pop(stack *s)
{
    if(s->currentsize == 0)
        return -1; // if stack is empty
    int popped;
    popped = s->array[(s->currentsize)-1];
    s->currentsize -=1;
    return  popped; // returns popped value
} // the stack  array will shrink STACK_BLOCK_SIZE entries at a time

stack *init_return(int towersize)
{
    stack *cr_stack = (stack*) malloc(sizeof(stack));
    cr_stack->array = (int *)malloc(STACK_BLOCK_SIZE*sizeof(int)); 
    cr_stack->maxsize = STACK_BLOCK_SIZE;
    cr_stack ->currentsize = 0;
    return cr_stack;
}; // initializes an empty stack

int init(stack *s)
{
    if(&s->array != NULL && (s != NULL) && (s->currentsize == 0) && (s->maxsize == STACK_BLOCK_SIZE) ) // if stack array is correctly initialized returns 1
        return 1;
    return 0; // else returns 0
} // returns 1 if initialization success

void move_block(stack *srcstack, stack *deststack,int a,int b)
{
    int srcblock = pop(srcstack); // popping src stacks last entry
    int destblock = pop(deststack); // popping dest stacks last entry
    int pushed;
    if(srcblock == -1) // if source pole  empty
    {
        pushed = push(srcstack,destblock);
        printf("Move the disk %d from '%d' to '%d' \n",pushed,b,a);
    }
    else if(destblock == -1) // if dest pole  empty
    {
        pushed = push(deststack,srcblock);
        printf("Move the disk %d from '%d' to '%d' \n",pushed,a,b);
    }
    else if(srcblock > destblock) // if source pole greater than dest pole
    {
        push(srcstack,srcblock);
        pushed = push(srcstack,destblock);
        printf("Move the disk %d from '%d' to '%d' \n",pushed,b,a);
    }
    else // if dest pole greater than source pole
    {
        push(deststack,destblock);
        pushed = push(deststack,srcblock);
        printf("Move the disk %d from '%d' to '%d' \n",pushed,a,b);
    }
}

int main()
{
    int towersize;
    long int total_move;
    int algo = 0;
    int a,b,c;
    printf("Enter tower size:");
    scanf("%d",&towersize);
    stack *s_stack; 
    stack *a_stack;
    stack *d_stack;
    total_move = pow(2,towersize) -1; // total number of moves
    do
    {
        s_stack = init_return(STACK_BLOCK_SIZE);
        a_stack = init_return(STACK_BLOCK_SIZE);
        d_stack = init_return(STACK_BLOCK_SIZE);
        a = init(s_stack);
        b = init(a_stack);
        c = init(d_stack);

    } while (!(a && b && c)); // while all stacks are correctly initialized.
    

    
    for(int i =towersize;i>0;i--) // fills the 1st tower source
    {
        push(s_stack,i);
    }
    if(towersize % 2 == 0) // algorithm changes if towersize even or odd
        algo = 1; // if towersize is even algo will change

    if(algo == 0) // if tower is odd
        {
            for(int i = 1;i<=total_move;i++) // each move
            {
                if(i % 3 == 0)
                    move_block(a_stack,d_stack,2,3);
                else if(i % 3 == 1)
                    move_block(s_stack,d_stack,1,3);
                else if(i % 3 == 2)
                    move_block(s_stack,a_stack,1,2);
                
            } 
        }
    
    else // even tower this time auxiliry(2) pole and destination(3) pole are swapped
    {
        for(int i = 1;i<=total_move;i++) // each move
            {
                if( i % 3 == 0)
                    move_block(d_stack,a_stack,3,2);
                else if(i % 3 == 1)
                    move_block(s_stack,a_stack,1,2);
                else if(i % 3 == 2)
                    move_block(s_stack,d_stack,1,3);
            }
    }
}