#include <stdio.h>
#include <string.h>

#include <sorter.h>
#include <util.h>

#define DEFAULT_LENGTH 25



int main(int argc, char* argv[])
{
    int length = DEFAULT_LENGTH;
    sortAlgorithm_t sortAlgorithm = INSERTION_SORT;
    int* array = NULL;
    if(argc>1)
    {
        if(strcmp(argv[1],"--help") ==0)
        {
            printf("1st input parameter 0/1 to select insertion/merge sort  Default insertion sort\n");
            printf("2nd input parameter  to select number of elements in the array \n");
        }
        if (sscanf (argv[1], "%i", (int*)&sortAlgorithm)!=1) {
            printf ("input arg error - not an integer"); 
            return -1;
        }
    }
    if(argc>2)
    {
        if (sscanf (argv[2], "%i", &length)!=1) {
            printf ("input arg error - not an integer"); 
            return -1;
        }
    }

    createRandomArray(length, &array); 
    printArray(length, array);
    profile();
    sort(length, &array, sortAlgorithm);  
    int timeTaken = profile();
    if(0 == timeTaken)
    {
        printf("Less than 1 second for sorting %d elements \n",length);
    }else
    {
        printf("Time for sorting %d elements is %d seconds  \n",length,timeTaken);
    }
    int isSorted = isArraySorted(length, array);
    if(isSorted)
    {
        printf("Array is sorted successfully \n");
    }else{
        printf("Array is not sorted !! \n");
    }

    printArray(length, array);
    return 0;
}



















