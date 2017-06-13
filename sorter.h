#ifndef __SORTER_H__
#define __SORTER_H__

typedef enum sortAlgorithm_t
{
    INSERTION_SORT,
    MERGE_SORT,
    SHELL_SORT,
    QUICK_SORT,
    COUNTING_SORT,
    RADIX_LSD_SORT,
    HEAP_SORT

}sortAlgorithm_t;
 

int sort(int*array, int length, sortAlgorithm_t alg);
int stringSort(char** array, int length, int stringLength, sortAlgorithm_t alg);


#endif
