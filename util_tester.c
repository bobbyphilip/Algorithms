#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <util.h>

#define DEFAULT_LENGTH 25

void test_shuffle(int arrayLength);
void test_random(int length);

int main(int argc, char* argv[])
{
    int length = DEFAULT_LENGTH;
    int test =0;
    if(argc>1)
    {
        if(strcmp(argv[1],"--help") ==0)
        {
            printf("1st input parameter 0 to select random array in a range (Default)\n");
            printf("1st input parameter 1 to select shuffle This will continue in a loop till Ctrl+C(Default)\n");
            printf("2nd input parameter  to select number of elements in the array (Default 25) \n");
        }
        if (sscanf (argv[1], "%i", (int*)&test)!=1) {
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
    switch(test)
    {
        case 0:
            test_random(length);
            break;
        case 1: 
            test_shuffle(length);
            break;
        default:
            printf("Invalid test case \n");
            break;
    }
    return 0;
}


void test_random(length)
{
    int i= 0;
    int r = 0;
    int *array;
    array = malloc(length*sizeof(int));
    memset(array,0,length*sizeof(int));
    int iterations = 1800000;
    while(i<iterations)
    {
        r = randomInRange(0,length-1);
        array[r]++;
        i++;
    }
#ifdef DEBUG
    printf("Ideal average value is %d \n",iterations/length);
    printf("Going to print frequency of each number in range 0-%d \n",length-1);
#else
    printf("Random generation test needs to be built with DEBUG=y to see o/p\n"); 
#endif
    printArray(array,length);
}

void test_shuffle(int arrayLength)
{
    int sum =0;
    int avg =0;
    int iter =0;
    int count =0;
    while(1)
    {
        int* array = NULL;
        createRandomArray(arrayLength,&array);
        printArray(array,arrayLength);
        int isSorted = isArraySorted(array, arrayLength);
        count =0;
        while(!isSorted)
        {
            count++;
            shuffle(array,arrayLength);
            isSorted = isArraySorted(array,arrayLength);
            if(isSorted)
            {
                sum+=count;
                iter++;
                avg = sum/iter;
                printf("Average runs for shuffle bogo sort  is %d after %d iterations \n",avg,iter);
            }
        }
        free(array);
    }
}




