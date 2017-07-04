#include <stdio.h>
#include <stdlib.h>

#include <util.h>
#include <sorter.h>

#define ARRAY_LENGTH 5

int main(int argc, char* argv[])
{
   int* a;
   int* b;
   int* c;
   createRandomArray(ARRAY_LENGTH, &a); 
   createRandomArray(ARRAY_LENGTH, &b); 
   createRandomArray(ARRAY_LENGTH, &c); 
    
   printArray(a,ARRAY_LENGTH);
   printArray(b,ARRAY_LENGTH);
   printArray(c,ARRAY_LENGTH);


   sort(a,ARRAY_LENGTH,INSERTION_SORT);
   sort(b,ARRAY_LENGTH,INSERTION_SORT);

/* increasing to the right and decreasing to bottom
  	a[0] a[1] a[2] a[3] a[4]
   b[4]
   b[3]
   b[2]
   b[1]
   b[0]
  
   start with a[0]+b[4] compare with c[0], go to the right if you need a bigger number down if smaller
 */
    int i =0;
    int j =ARRAY_LENGTH-1;
    int k =0;
    for(k =0; k<ARRAY_LENGTH;k++)
    {
        while(i>=0 && i< ARRAY_LENGTH && j>=0 && j<ARRAY_LENGTH)
	{
	     int sum = a[i]+b[j]+c[k];
	     if(sum ==0)
	     {
		printf("Found !!  %d  %d  %d \n",a[i],b[j],c[k]);
		return 0;
             }else if(sum >0)
	     {
               //Need a smaller number
               j--;
             }else
	     {
		i++;
	     }
	}
    }
    printf("Not Found \n");	
    return -1;
  
}
 


