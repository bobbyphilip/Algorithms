#ifndef __MAXBINARYHEAP_H__
#define __MAXBINARYHEAP_H__


typedef struct BinaryHeap
{
 int* array;
 int arrayLength;
 int heapSize;

}BinaryHeap;

void maxHeapify(BinaryHeap* binaryHeap, int index);
void buildMaxHeap(BinaryHeap* heap);

#define PARENT(i) (i-1)/2
#define LEFT(i) 2*i+1
#define RIGHT(i) 2*i+2

#endif
