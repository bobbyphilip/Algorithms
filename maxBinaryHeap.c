#include <stdio.h>
#include <maxBinaryHeap.h>
#include <util.h>
#include <stdlib.h>

/*
 For an n-element heap, leaves are at n/2 +1, n/2 +2 ...n
 heapSize-1 is done because element x will be at array position x-1
 All the leaves are 1 element max-heaps
*/

void buildMaxHeap(BinaryHeap* heap)
{
    int i =0;
    for(i=((heap->heapSize-1)/2);i>=0;i--)
    {
	maxHeapify(heap, i);
    }	
}

/*
 Idea is all the nodes below(after) index follow maxHeap property (ie; parent is >= node)
 element at index might not follow this. So we want to push it to its position. First find larger of its two children, swap with it. 
 Then recursively run this at the changed node
*/ 
void maxHeapify(BinaryHeap* binaryHeap, int index)
{
    int* array = binaryHeap->array;
    int left = LEFT(index);
    int right = RIGHT(index);
    
    int largest = index;
    if((left < binaryHeap->heapSize) && array[left] > array[largest])
    {
  	largest = left;
    }
    if( (right<binaryHeap->heapSize) && array[right]> array[largest])
    {
        largest = right;
    }
    if(largest != index)
    {
	swap(array, largest, index);
 	maxHeapify(binaryHeap, largest);
    }
}


int heapMaximum(BinaryHeap* heap)
{
    return heap->array[0];

}



int heapExtractMaximum(BinaryHeap* heap)
{
   int maximum = heap->array[0];
   heap->array[0] = heap->array[heap->heapSize -1];
   heap->heapSize--; 
   maxHeapify(heap, 0);
   return maximum;
}


void heapIncreaseKey(BinaryHeap* heap, int index, int key)
{
   int* array = heap->array;
   if(key <= heap->array[index])
   {
	printf("New key has to be greater!! \n");
	return;
   }
   heap->array[index] = key;
   int parentIndex = PARENT(index);
   while(index> 0 && array[parentIndex] < array[index]) 
   {
	swap(array, parentIndex, index);
        index = parentIndex;
   }
}


void heapInsert(BinaryHeap* heap, int key)
{
     if(heap->heapSize == heap->arrayLength)
     {
         heap->arrayLength*=2;
         heap->array = realloc(heap->array, heap->arrayLength);
     }
     heap->heapSize++;
     heap->array[heap->heapSize -1] = -0x80000000;
     heapIncreaseKey(heap,heap->heapSize-1,key);

}



