#include <sorter.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SHELL_INC_TOTAL 16
static void insertionSort(int* array, int length);  
static void mergeSort(int* array, int start, int end);  
static void merge(int* array, int start, int mid, int end);
static void shellSort(int* array, int length);  

/* Magic Constants from Sedgewick*/
static const int shellIncrements[SHELL_INC_TOTAL] = {1391376, 463792, 198768, 86961,
             33936, 13776, 4592, 1968, 861,
             336, 112, 48, 21, 7, 3, 1};

/* Used in merge sort for memory */
int* left = NULL;
int* right = NULL;
/**
 * To classify  n bits of data
 * n! possible arrangements
 * With binary questions
 * n! ~ 2^k
 * log(N!) ~= log(N^N) = NlogN = klog2 = k
 * Which becomes the best case
 * To beat this barrier we have to do better than binary classification( radix, counting. bucket)
 */

int sort(int*array, int length, sortAlgorithm_t alg)
{
    switch(alg)
    {
        case INSERTION_SORT:
            insertionSort(array, length);
            return 0;
            break;
        case MERGE_SORT:
            mergeSort(array,0,length-1);
            return 0;
            break;
        case SHELL_SORT:
            shellSort(array,length);
            return 0;
        default:
            printf("Invalid Input\n");
            return -1;
    }
}

/**
 * Insertion worst case is O(N^2), avg is O(N^2)
 * Stable
 * In-Place
 * Good performance if array is already nearly sorted, since number of swaps required will be less
 */
static void insertionSort(int* inputArray, int length)
{
    int i=1;
    int j=0;
    for(i=1;i<length;i++)
    {
        int key = inputArray[i]; 
        j=i-1; 
        while((j>=0) && (inputArray[j]>key))
        {
            inputArray[j+1]= inputArray[j];
            j--;
        }
        inputArray[j+1]= key; 
    } 
} 

/**
 * Divide and conquer, split array into two, recursively sort them and merge
 * T(N) = N(for the merge) + T(N/2) + T(N/2)
 * Guessing T(N) = NlogN, the identity is correct, proving the performance is O(NlogN)
 * Not In place. Need auxillary O(N) space
 * Here splitting is linear operation while the merge takes time
 * Stable
 */
static void mergeSort(int* array, int start, int end)
{
    static int recursionCounter =0;
    recursionCounter++;
    if(start<end)
    {
        int split = start + (end-start)/2;
        if(left == NULL )
        {
            left = malloc(sizeof(int)*(split+1));
            right = malloc(sizeof(int)*(split+1));
        }
        mergeSort(array,start,split);
        mergeSort(array,split+1,end);
        merge(array,start,split,end);
    }
    recursionCounter--;
    if(recursionCounter == 0)
    {
        free(left);
        free(right);
        left = NULL;
        right = NULL;
    }
}


static void merge(int* arrayRef, int start, int mid, int end)
{
    int leftLength = mid-start+1;
    int rightLength = end-mid;
    int i=0;
    int leftCounter = 0;
    int rightCounter =0;
    
    memcpy(left,arrayRef+start,sizeof(int)*leftLength);
    memcpy(right,arrayRef+mid+1,sizeof(int)*rightLength);
    i=start;
    if(left[leftLength-1] > right[0])
    {
    for(i=start;i<end+1;i++)
    {
        if((leftCounter==leftLength) || (rightCounter==rightLength))
        {
            break;
        }
        if(left[leftCounter] <= right[rightCounter])
        {
            arrayRef[i] = left[leftCounter++];
        }else
        {
            arrayRef[i] = right[rightCounter++];
        }
    }
    }
    if(i<end+1)
    {
        while(leftCounter<leftLength)
        {
            arrayRef[i++] = left[leftCounter++];
        }
        while(rightCounter<rightLength)
        {
            arrayRef[i++] = right[rightCounter++];
        }
    }
}


/**
 * If an array is k-sorted and then j-sorted it remains k-sorted
 * Idea is bring in order far apart elements faster than something like insertion sort
 * For eg: first 7 sort, then 4 sort, then 1 sort
 * Constants defined are important. Using Sedgewick's values here
 * Compared to insertion sort, number of swaps measured to be much lower
 */
static void shellSort(int* array, int length)
{
    int gapCount = 0;
    while(gapCount< SHELL_INC_TOTAL)
    {
        int gap = shellIncrements[gapCount];
        int i=0;
        int j=0;
        for(i=gap;i<length;i++)
        {
            int key = array[i];
            j=i-gap;
            while((j>=0) && (array[j]>key))
            {
                array[j+gap] = array[j];
                j-= gap;
            }
            array[j+gap] = key;
        }
        gapCount++;
    }
}














