#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <util.h>

#define DEFAULT_ROTATE 4
#define DEFAULT_LENGTH 10


static void reverseString(char* string, int startPoint, int endPoint)
{
    char* endPointer = &string[endPoint-1];
    char* startPointer = &string[startPoint];

    while(startPointer<endPointer) 
    {
        char temp= *startPointer;
        *startPointer = *endPointer;
        *endPointer = temp;
        startPointer++;
        endPointer--;
    }

}

static void rotateString(char* string, int rotateFactor)
{
    int length = strlen(string);
    rotateFactor%= length;
    reverseString(string,0,rotateFactor);
    reverseString(string,rotateFactor,length);
    reverseString(string,0,length);
}

/*
 * Solution described in the book programming pearls
 */
int main(int argc, char* argv[])
{
    int rotate =DEFAULT_ROTATE;
    int length = DEFAULT_LENGTH;
    char* inputString= NULL;
    if(argc>1)
    {
        if(strcmp(argv[1],"--help") ==0)
        {
            printf("1st input argument number to rotate the string by (default 4) \n");
            printf("2nd input argument the string to rotate ( default randomly generated length 10)\n");
        }else if (sscanf (argv[1], "%i", (int*)&rotate)!=1) {
            printf ("input arg error - not an integer"); 
            return -1;
        }
    }
    if(argc >2)
    {
        length = strlen(argv[2]);
        inputString = malloc(length);
        strcpy(inputString,argv[2]);
    }else
    {
        createRandomString(&inputString,length);
    }


    printf("String input is %s \n",inputString);
    rotateString(inputString,rotate);
    printf("String rotated by %d %s \n",rotate,inputString);
    free(inputString);
    return 0;
}


