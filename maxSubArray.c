#include <stdio.h>
#include <stdlib.h>

#include <util.h>

#define DEFAULT_LENGTH 10



int main(int argc, char* argv[])
{
    int length = DEFAULT_LENGTH;
    int* array = NULL;
    if(argc>1)
    {
        if (sscanf (argv[1], "%i", (int*)&length)!=1) {
            printf ("input arg error - not an integer"); 
            return -1;
        }
    }
        
    createRandomArray(length, &array); 
   
    printArray(array, length);

    int maxOverall = array[0];
    int runningMax = array[0];

    int i=0, startIndex =0, endIndex =0, runStart =0, runEnd =0;
    for(i=1;i<length;i++)
    {
	if(array[i]< (runningMax+array[i]))
	{
	     runningMax+= array[i];
	     runEnd =i;
	} else 
	{
	     runningMax = array[i];
	     runStart =i;
	     runEnd =i;
	}
        if( maxOverall < runningMax)
	{
	    maxOverall = runningMax;
	    startIndex = runStart;
	    endIndex = runEnd;
	} 
    } 
    printf("Max subarray sum is %d from %d to %d \n",maxOverall, startIndex, endIndex);
 
    free(array);
    return 0;
}



















