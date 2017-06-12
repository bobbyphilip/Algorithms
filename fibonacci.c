
#include <stdio.h>

int fibonacci(int element);


int main(int argc, char* argv[])
{
    int fibonacciElement = 10;
    if(argc>1)
    {
        if (sscanf (argv[1], "%i", (int*)&fibonacciElement)!=1) {
            printf ("input arg error - not an integer"); 
            return -1;
        }
        if(fibonacciElement < 1)
        {
            printf("Needs to be greater than 0 \n");
            return -1;
        }
    }
    int answer = fibonacci(fibonacciElement);
    printf("Number %d in the fibonacci series is %d \n",fibonacciElement, answer);
    
}

int fibonacci(int element)
{
    if((element == 0) || (element ==1))
    {
        return element;
    }
    return fibonacci(element-1) + fibonacci(element -2);
}
    
    

