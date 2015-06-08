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

void createRandomStrings(int length, int stringLength, char*** array)
{
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    srandom(time(NULL));
    char** createdArray = malloc(sizeof(char*)*length);
    int i=0;
    int j=0;
    for(i=0;i<length;i++)
    {
        createdArray[i] = malloc(sizeof(char)*stringLength);
        for(j=0;j<stringLength-1;j++)
        {
    
            createdArray[i][j]= alphanum[random()%(sizeof(alphanum)-1)];
        }
        createdArray[i][j]= '\0';
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



void printStringArray(char** array, int length)
{
#ifdef DEBUG
    int i =0;
    if(length==0)
    {
        printf("[]");
        return;
    }
    printf("[%s",array[0]);
    for(i=1;i<length;i++)
    {
        printf(", %s",array[i]);
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

