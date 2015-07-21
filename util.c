#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <util.h>

//#define DEBUG 1
static int profileTime;

static int randomSeeded = 0;

void createRandomArray( int length, int** array)
{
    if(!randomSeeded)
    {
        srandom(time(NULL));
        randomSeeded =1;
    }
    int* createdArray = malloc(sizeof(int)*length);
    int i=0;
    for(i=0;i<length;i++)
    {
        //Not ideal! Using % doesnt produce a uniformly distributed sequence
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

/*
 * Generates random numbers in range start -end ( inclusive)
 * https://stackoverflow.com/questions/2509679/how-to-generate-a-random-number-from-within-a-range
 * Related interesting question https://stackoverflow.com/questions/137783/expand-a-random-range-from-1-5-to-1-7
 * Reason why % doesnt work perfectly
 * random() generates b/w 0-RAND_MAX
 * If RAND_MAX is not a multiple of your range, then some numbers in your range will be over represented
 */
int randomInRange(int start, int end)
{
    if(end<start)
    {
        printf("Input error \n");
        return 4;//XKCD approved random ;-)
    }
    if(!randomSeeded)
    {
        srandom(time(NULL));
        randomSeeded =1;
    }
    int range = end-start+1;
    int maxRandomRange = RAND_MAX -(RAND_MAX%range);
    int bucketSize = maxRandomRange/range;
    int r =0;
    do{
        r= random();
    }while(r>=maxRandomRange);

    r = r/bucketSize;
    return start+ r;
}

/**
 * Knuth shuffle.
 * swaps element at array[i] with number at arrayy[randpom->0-i)
 * Taking random over whole range is wrong.
 * For example for 3 cards.
 * total permutation is 3!
 * Using random for full range possibilities are 3^3 =27
 * which will result in skewed result since 27%6 !=0
 */
void shuffle(int* array, int length)
{
    int i=0;
    int r =0;
    for(i=0;i<length;i++)
    {
       
        r = randomInRange(0,i);
        swap(array,i,r);
    }
}

void swap(int* array, int i, int j)
{
    int temp = array[i];
    array[i] = array[j];
    array[j]=temp;
}

