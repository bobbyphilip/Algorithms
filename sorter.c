#include <sorter.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <maxBinaryHeap.h>


#define SHELL_INC_TOTAL 16
static void insertionSort(int* array, int length);  

static void mergeSort(int* array, int start, int end);  
static void merge(int* array, int start, int mid, int end);
/* Used in merge sort for memory */
int* leftArray = NULL;
int* rightArray = NULL;

static void shellSort(int* array, int length);  
/* Magic Constants from Sedgewick*/
static const int shellIncrements[SHELL_INC_TOTAL] = {1391376, 463792, 198768, 86961,
             33936, 13776, 4592, 1968, 861,
             336, 112, 48, 21, 7, 3, 1};


static void quickSort(int* array, int start, int end);  
static int partition(int* array, int start, int end);
static int median(int* array, int start, int end);
static void swapIfNeeded(int* array, int a, int b);
static void swap(int* array, int a, int b);


static void countingSort(int* array, int length, int base);

static void radixLsdSort(char** array, int length, int stringLength);

static void heapSort(int* array, int length);  
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
            printf("Insertion sort \n");
            insertionSort(array, length);
            return 0;
            break;
        case MERGE_SORT:
            printf("Merge sort \n");
            mergeSort(array,0,length-1);
            return 0;
            break;
        case SHELL_SORT:
            printf("Shell sort \n");
            shellSort(array,length);
            return 0;
        case QUICK_SORT:
            printf("Quick  sort \n");
            quickSort(array,0,length-1);
            return 0;
            break;
        case COUNTING_SORT:
            //length*10 because that is how the randown numbers are generated in util.c
            //This wont really prove the efficiency of counting sort
            printf("Counting sort \n");
            countingSort(array,length,length*10);
            return 0;
            break;
        case HEAP_SORT:
            printf("HEAP sort \n");
            heapSort(array,length);
            return 0;
            break;
        default:
            printf("Invalid Input\n");
            return -1;
    }
}

int stringSort(char** array, int length, int stringLength, sortAlgorithm_t alg)
{
    switch(alg)
    {
        case RADIX_LSD_SORT:
            radixLsdSort(array, length, stringLength);
            break;
        default:
            printf("Invalid Input\n");
            return -1;
    }
    return 0;
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
        if(leftArray == NULL )
        {
            leftArray = malloc(sizeof(int)*(split+1));
            rightArray = malloc(sizeof(int)*(split+1));
        }
        mergeSort(array,start,split);
        mergeSort(array,split+1,end);
        merge(array,start,split,end);
    }
    recursionCounter--;
    if(recursionCounter == 0)
    {
        free(leftArray);
        free(rightArray);
        leftArray = NULL;
        rightArray = NULL;
    }
}


static void merge(int* arrayRef, int start, int mid, int end)
{
    int leftLength = mid-start+1;
    int rightLength = end-mid;
    int i=0;
    int leftCounter = 0;
    int rightCounter =0;

    memcpy(leftArray,arrayRef+start,sizeof(int)*leftLength);
    memcpy(rightArray,arrayRef+mid+1,sizeof(int)*rightLength);
    i=start;
    if(leftArray[leftLength-1] > rightArray[0])
    {
        for(i=start;i<end+1;i++)
        {
            if((leftCounter==leftLength) || (rightCounter==rightLength))
            {
                break;
            }
            if(leftArray[leftCounter] <= rightArray[rightCounter])
            {
                arrayRef[i] = leftArray[leftCounter++];
            }else
            {
                arrayRef[i] = rightArray[rightCounter++];
            }
        }
    }
    if(i<end+1)
    {
        while(leftCounter<leftLength)
        {
            arrayRef[i++] = leftArray[leftCounter++];
        }
        while(rightCounter<rightLength)
        {
            arrayRef[i++] = rightArray[rightCounter++];
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



/**
 * Shuffle the array.
 * partition for some i, element[i] in place, if j<i => a[j]<=a[i], j>i => a[j]>=a[i]
 * sort each sub-part recursively
 * T(N) = N(for the split) + T(N/2) + T(N/2)
 * Unstable
 * Best O(NlogN), avg O(NlogN), worst O(N^2) --rare
 * space complexity O(N)/O(logN)
 * Not the most efficient of implementations.
 * Since the input from the driver is random, not shuffling it here
 * Implementation is as follows, partition the array into two, leaving the median there
 * Recursively sort the 2 sides
 * If total elements to be sorted in a call to this API is small, good idea to used insertion sort
 * Java uses 7 as threshold, qsort uses 4
 */
static void quickSort(int* array, int start, int end)
{
    if(start<end)
    {
        int mid = partition(array, start, end);
        quickSort(array, start, mid-1);
        quickSort(array, mid+1, end);
        
    }
}

/*
 * Finds a  median of the first, middle and end elements
 * Moves the median element to the end of the array
 * Takes the elements of the array from start to end
 * Track a position to store the median.
 * Array elements get put to the left/right of this
 * At the end median is put into this tracked position
 */
static int partition(int* array, int start, int end)
{
    int medianIndex = median(array, start, end);
    int medianValue = array[medianIndex];
    
    swap(array, medianIndex, end);
    
    int pivot = start;
    int i;
    for(i = start; i<end;i++)
    {
        if(array[i]<= medianValue)
        {
            swap(array,i,pivot);
            pivot++;
        }
    }
    swap(array,pivot,end);
    return pivot;
}



static int median(int* array, int start, int end)
{
    if((end-start) <2)
    {
        return start;
    }
    int middle = start + (end-start)/2;
    /*
     * Sorting using sorting network
     * SWAPs needed generated from the awesome page
     * pages.ripco.net/~jgamble/nw.html
     */
    swapIfNeeded(array, middle, end);
    swapIfNeeded(array, start, end);
    swapIfNeeded(array, start, middle);
    /*
     * at this point the three elements are sorted among themselves.
     *Returning the median
     * Changing the order doesnt matter, since quick sort is anyway unstable
     */
    return middle;
}


/*
 * Does a compare and swaps if a> b
 */
static void swapIfNeeded(int* array, int a, int b)
{
    if(array[a] >array[b])
    {
        swap(array, a, b);
    }
}     


static void swap(int* array, int a, int b)
{
    int temp = array[a];
    array[a] = array[b];
    array[b] = temp;
}




/**
 * Linear time sorting, done by moving from the comparision model which has the limit O(NlogN)
 * Integer sorting as example
 * keys to be sorted which are integers in range {0,1,2....k-1}
 * If k is not too large, then O(N)
 */




/**
 * Counting sort is of order O(N+K)
 * Space O(N+K)
 * initialise an counting array of length k (0-k-1) to zero
 * Go over the n inputs incrementing countingArray[n]
 * to finish the sort iterate over the countingArray, 
 * output[i++] = while(countingArray[j]!= 0) j, decrementing countingArray[j],and going forward by incremening j
 * But this is not stable, one way is to keep a linked list at each node of the counting array
 * Implementation below is stable
 */


//Doesnt work right now with negative arrays
static void countingSort(int* array, int length, int base)
{
   //Hack, converting input array to all positive number
   int i=0;
   for(i=0;i<length;i++)
   {
       if(array[i]<0)
          array[i]*= -1;
   }
   int* pos = malloc(base*sizeof(int));
   int* temp= malloc(length*sizeof(int));
   if(NULL==pos || NULL==temp)
   {
       printf("malloc failed \n");
       return;
   }
   memset(pos,0,base*sizeof(int));
   memset(temp,0,length*sizeof(int));
   for(i=0;i<length;i++)
   {
       pos[array[i]]++;
   }
   for(i=1;i<base;i++)
   {
       pos[i] = pos[i] + pos[i-1];
   }
   /**
    * At this point the cumulative counts are obtained.
    * Each index will be the sum of all the elements <= that number
    */
   for(i=0;i<length;i++)
   {
       if(array[i] ==0)
           continue;
       int index = pos[array[i]-1];
       /**
        * Index will give how many elements to the left of this element are there
        */
       temp[index]= array[i];
       pos[array[i]-1]++;

   }
   memcpy(array,temp,length*sizeof(int));
   free(temp);
   free(pos);

}

/**
 * Radix sort
 * Imagine integers as in base b
 * #digits is d = log(k) to the base d, where k is maximum value of keys
 * Sort number by LSD the next .etc. ( O(N+b))
 * Total becomes O( (N+b) log(k)) which can result in linear
 */

static void radixLsdSort(char** array, int length, int stringLength)
{
    int pos[256];
    char** temp = malloc(length*sizeof(char*));
    int i =0;
    int stringIndex =stringLength -1;
    while(stringIndex != 0)
    {
        memset(temp, 0, length*sizeof(char*));
        memset(pos,0,256*sizeof(int));

        for(i=0;i<length;i++)
        {
            pos[(int)array[i][stringIndex-1]]++;
        }
        for(i=1;i<256;i++)
        {
            pos[i]+=pos[i-1];
        }
        
        int index=0;     
        for(i=0;i<length;i++)
        {
            index = pos[array[i][stringIndex-1]-1];
        //    strncpy(temp[index],array[i],stringLength);
            temp[index] = array[i];
            pos[array[i][stringIndex-1]-1]++;
        }
        for(i=0;i<length;i++)
        {
          //  strncpy(array[i],temp[i],stringLength);
            array[i] = temp[i];
        }
        stringIndex--;
    }
}




static void heapSort(int* array, int length)
{
   BinaryHeap* heap = malloc(sizeof(BinaryHeap));
   heap->array = array;
   heap->heapSize = length;
   heap->arrayLength = length;

   buildMaxHeap(heap);
   int i = 0;
   /*
    Largest element moved out to end of array, the remaining elements are max-heapified
    Continously doing thus gets the sorted array
    */
   for(i= length-1;i>0;i--)
   {
	swap(heap->array,i,0);
        heap->heapSize--;
        maxHeapify(heap, 0);
   }

}



