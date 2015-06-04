#ifndef __SORTER_H__
#define __SORTER_H__

typedef enum sortAlgorithm_t
{
    INSERTION_SORT,
    MERGE_SORT,
    SHELL_SORT,
    QUICK_SORT
}sortAlgorithm_t;
 

int sort(int*array, int length, sortAlgorithm_t alg);


#endif
