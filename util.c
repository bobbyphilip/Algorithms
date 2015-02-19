#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "util.h"

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

void printArray(int length, int*array)
{
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
}
