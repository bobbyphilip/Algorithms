#include <stdio.h>
#include <string.h>

#include <sorter.h>
#include <util.h>

#define DEFAULT_LENGTH 25



int main(int argc, char* argv[])
{
   int length = DEFAULT_LENGTH;
   sortAlgorithm_t sortAlgorithm = INSERTION_SORT;
   int* array = NULL;
   if(argc>1)
   {
       if(strcmp(argv[1],"--help") ==0)
       {
           printf("1st input parameter 0/1 to select insertion/merge sort  Default insertion sort\n");
           printf("2nd input parameter  to select number of elements in the array \n");
       }
       if (sscanf (argv[1], "%i", (int*)&sortAlgorithm)!=1) {
           printf ("input arg error - not an integer"); 
           return -1;
       }
   }
   if(argc>2)
   {
       if (sscanf (argv[2], "%i", &length)!=1) {
           printf ("input arg error - not an integer"); 
           return -1;
       }
   }
   
   createRandomArray(length, &array); 
   printArray(length, array);
   sort(length, &array, sortAlgorithm);  
   printArray(length, array);
   return 0;
}



















