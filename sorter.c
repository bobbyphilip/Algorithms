#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define DEFAULT_LENGTH 25

void createRandomArray( int length, int** array);
void printArray(int length, int*array);
void insertionSort(int length, int**array);  
void mergeSort(int**array, int start, int end);  
void merge(int**array, int start, int mid, int end);

#define INSERTION_SORT 0
#define MERGE_SORT 1

int main(int argc, char* argv[])
{
   int length = DEFAULT_LENGTH;
   int sortType = INSERTION_SORT;
   int* array = NULL;
   if(argc>1)
   {
       if(strcmp(argv[1],"--help") ==0)
       {
           printf("1st input parameter 0/1 to select insertion/merge sort  Default insertion sort\n");
           printf("2nd input parameter  to select number of elements in the array \n");
       }
       if (sscanf (argv[1], "%i", &sortType)!=1) {
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
   if(sortType == INSERTION_SORT)
   {
       insertionSort(length, &array);  
   } else if(sortType == MERGE_SORT)
   {
       mergeSort(&array, 0, length-1);
   }
   printArray(length, array);
   return 0;
}

void insertionSort(int length, int**array)
{
    int* inputArray = *array;
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


void mergeSort(int**array, int start, int end)
{
    if(start<end)
    {
        int split = (start+end)/2;
        mergeSort(array,start,split);
        mergeSort(array,split+1,end);
        merge(array,start,split,end);
    }
}

void merge(int**array, int start, int mid, int end)
{
    int* arrayRef = *array;
    int* left = malloc(sizeof(int)*(mid-start+1));
    int* right = malloc(sizeof(int)*(end-mid));
    int i=0;
    for(i=0;i<(mid-start+1);i++)
    {
        left[i] = arrayRef[start+i];
    }
    for(i=0;i<end-mid;i++)
    {
        right[i] = arrayRef[mid+1+i];
    }
    int leftCounter = 0;
    int rightCounter =0;
    int leftLength = mid-start+1;
    int rightLength = end-mid;
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
    free(left);
    free(right);
}


















