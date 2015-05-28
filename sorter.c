#include <sorter.h>
#include <stdio.h>
#include <stdlib.h>
static void insertionSort(int**array, int length);  
static void mergeSort(int**array, int start, int end);  
static void merge(int**array, int start, int mid, int end);


int sort(int**array, int length, sortAlgorithm_t alg)
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


void insertionSort(int**array, int length)
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
