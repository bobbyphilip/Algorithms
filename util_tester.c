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
            printf("1st input parameter 1 to select shuffle (Default)\n");
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
        case 1: 
            test_shuffle(length);
            break;
        default:
            test_random(length);
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
    while(i<1800000)
    {
        r = randomInRange(0,length-1);
        array[r]++;
        i++;
    }
#ifdef DEBUG
    printf("Going to print occurences of each element \n");
#endif
    printArray(array,length);
}

void test_shuffle(int arrayLength)
{
    int* array = NULL;
    createRandomArray(arrayLength,&array);
    printArray(array,arrayLength);
    shuffle(array,arrayLength);
    printArray(array,arrayLength);
    free(array);
}




