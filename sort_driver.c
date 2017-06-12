#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
            printf("1st input parameter 0 to select insertion sort  (Default)\n");
            printf("1st input parameter 1 to select merge sort  \n");
            printf("1st input parameter 2 to select shell sort\n");
            printf("1st input parameter 3 to select quick sort\n");
            printf("1st input parameter 4 to select counting sort\n");
            printf("1st input parameter 5 to select string radix lsd sort\n");
            printf("2nd input parameter  to select number of elements in the array (Default 25) \n");
            return 0;
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

    if(RADIX_LSD_SORT == sortAlgorithm)
    {
        printf("Radix LSD Sort \n");
        char** stringArray = NULL;
        createRandomStringArray(length+1, 9, &stringArray);
        printStringArray(stringArray, length);
        profile();
        stringSort(stringArray,length, 9, sortAlgorithm);
        int timeTaken = profile();
        if(0 == timeTaken)
        {
            printf("Less than 1 second for sorting %d elements \n",length);
        }else
        {
            printf("Time for sorting %d elements is %d seconds  \n",length,timeTaken);
        }
        printStringArray(stringArray, length);
        return 0;
    }
    

    createRandomArray(length, &array); 
    printArray(array, length);
    profile();
    sort(array, length, sortAlgorithm);  
    int timeTaken = profile();
    if(0 == timeTaken)
    {
        printf("Less than 1 second for sorting %d elements \n",length);
    }else
    {
        printf("Time for sorting %d elements is %d seconds  \n",length,timeTaken);
    }
    
    int isSorted = isArraySorted(array, length);
    if(isSorted)
    {
        printf("Array is sorted successfully \n");
    }else{
        printf("Array is not sorted !! \n");
    }

    printArray(array, length);
    free(array);
    return 0;
}



















