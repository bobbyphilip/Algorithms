#ifndef __MAXPRIORITYQUEUE_H__
#define __MAXPRIORITYQUEUE_H__

#include <maxBinaryHeap.h>

int heapMaximum(BinaryHeap* heap);
int heapExtractMaximum(BinaryHeap* heap);
void heapIncreaseKey(BinaryHeap* heap, int index, int key);
void heapInsert(BinaryHeap* heap, int key);

#endif
