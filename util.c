#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <util.h>

//#define DEBUG 1
static int profileTime;

void createRandomArray( int length, int** array)
{
    srandom(time(NULL));
    int* createdArray = malloc(sizeof(int)*length);
    int i=0;
    for(i=0;i<length;i++)
    {
        createdArray[i]= random()%(length*10);
    }
    *array = createdArray;
} 

void printArray(int*array, int length)
{
#ifdef DEBUG
    int i =0;
    if(length==0)
    {
        printf("[]");
        return;
    }
    printf("[%d",array[0]);
    for(i=1;i<length;i++)
    {
        printf(", %d",array[i]);
    }
    printf("]\n");
#endif
}

int isArraySorted(int*array, int length)
{
    int i =0;
    for(i=0;i<length-1;i++)
    {
        if(array[i]>array[i+1])
        {
            return 0;
        }
    }
    return 1;

}

int profile()
{
    struct timespec spec;
    int currTime =profileTime;
    clock_gettime(CLOCK_REALTIME, &spec);
    profileTime = spec.tv_sec;
    return (profileTime - currTime); 
}

