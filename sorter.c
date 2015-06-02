#include <sorter.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void insertionSort(int* array, int length);  
static void mergeSort(int* array, int start, int end);  
static void merge(int* array, int start, int mid, int end);


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
        default:
            printf("Invalid Input\n");
            return -1;
    }
}


void insertionSort(int* inputArray, int length)
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


void mergeSort(int* array, int start, int end)
{
    if(start<end)
    {
        int split = (start+end)/2;
        mergeSort(array,start,split);
        mergeSort(array,split+1,end);
        merge(array,start,split,end);
    }
}


void merge(int* arrayRef, int start, int mid, int end)
{
    int leftLength = mid-start+1;
    int rightLength = end-mid;
    int* left = malloc(sizeof(int)*leftLength);
    int* right = malloc(sizeof(int)*rightLength);
    int i=0;
    int leftCounter = 0;
    int rightCounter =0;
    
    memcpy(left,arrayRef+start,sizeof(int)*leftLength);
    memcpy(right,arrayRef+mid+1,sizeof(int)*rightLength);
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
