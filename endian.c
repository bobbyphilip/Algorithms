#include <stdio.h>

int main(int argc, char* argv[])
{
  unsigned int x =1;
printf("ENTER\n");
  char* ptr =(char*) &x;
  if(*ptr == 0)
  printf("BE\n");
else
printf("LE \n");
}
