#include <stdio.h>
#include <maxBinaryHeap.h>
#include <maxPriorityQueue.h>
#include <util.h>
#include <stdlib.h>


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






