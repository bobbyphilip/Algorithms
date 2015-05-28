#ifndef __SORTER_H__
#define __SORTER_H__

typedef enum sortAlgorithm_t
{
    INSERTION_SORT,
    MERGE_SORT
}sortAlgorithm_t;
 

int sort(int length, int**array, sortAlgorithm_t alg);


#endif
