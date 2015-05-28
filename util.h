#ifndef __UTIL_H__
#define __UTIL_H__

void createRandomArray( int length, int** array);
void printArray(int*array, int length);
/*
 * Returns 1 if sorted in ascending order
 */
int isArraySorted(int*array, int length);
/*
 * Simplistic API which returns time elapsed in seconds since the last call to this API
 */
int profile();


#endif
