#include <stdio.h>
#include <stdlib.h>

#include <util.h>
#include <sorter.h>

#define DEFAULT_LENGTH 10

int partition(int* array, int start, int end);
int quickSelect(int* array, int start, int end, int indexToFind);

int main(int argc, char* argv[])
{
    int length = DEFAULT_LENGTH;
    int* array = NULL;
    if(argc>1)
    {
        if (sscanf (argv[1], "%i", (int*)&length)!=1) {
            printf ("input arg error - not an integer"); 
            return -1;
        }
    }
    int indexToFind =  length/2;
    if(argc>2)
    {
        if (sscanf (argv[2], "%i", (int*)&indexToFind)!=1) {
            printf ("input arg error - not an integer"); 
            return -1;
        }
    }
    if(indexToFind>=length)
    {
      indexToFind = length -1;
    }
    printf("Going to find element at index %d \n ",indexToFind);
    createRandomArray(length, &array);
    printArray(array, length);
    int result = quickSelect(array, 0, length-1, indexToFind);
    printf("The element at position %d is %d \n",indexToFind,result);
    sort(array,length, 3);
    printf("The element from the sorted array at position %d is %d \n",indexToFind,array[indexToFind]);
    if(array[indexToFind] == result)
    {
      printf("Quick select successful\n");
    } else
    {
	printf("ERROR in quickselect\n\n");
    }
  
    free(array);
    return 0;
}



int quickSelect(int* array, int start, int end, int indexToFind)
{
   if(start >=end)
   {
      return array[start];	
   }
   int pivot = partition(array,start,end);
   if(pivot ==indexToFind)
   {
   	return array[indexToFind];
   } else if( pivot< indexToFind)
   {
	return quickSelect(array,pivot+1,end, indexToFind);	
   }else 
   {
	return quickSelect(array,start,pivot-1, indexToFind);
   }

}


int partition(int* array, int start, int end)
{
   int randIndex = randomInRange(start,end);
   swap(array, randIndex,end);
   int pivot = start;
   int i;
   for(i=start;i<end;i++)
   {
	if(array[i]<array[end])
        {
           swap(array, i, pivot);
           pivot++;
        }
   }
   swap(array,pivot,end);
   return pivot;

}
















