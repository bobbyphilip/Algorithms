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

int heapMaximum(int* array);
int heapExtractMaximum( int* array, int length);
void heapIncreaseKey(int* array, int length, int index, int key);
void heapInsert(int* array, int key);

#endif
