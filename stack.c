#include <stdio.h>
#include <stdlib.h>
#include <util.h>

typedef struct Stack
{
 int* array;
 int top;
 int stackSize;
}Stack;

typedef struct QueueWithStack
{
   Stack* stack1;
   Stack* stack2;
}

void initStack(Stack* stack, int size)
{
    stack->array = malloc(size* sizeof(int));
    stack->top =0;
    stack->stackSize = size;
}

int isEmpty(Stack* stack)
{
   return (stack->top ==0 ? 0:1);
}

int isFull(Stack* stack)
{
   return (stack->top ==stack->stackSize ? 1:0);
}

void push(Stack* stack, int data)
{
   if(!isFull(stack))
   {
      stack->array[stack->top] = data;
      stack->top++
   }else
   {
	printf("Error the stack is full\n");
   }
}


int pop(Stack* stack)
{
   if(!isEmpty(stack))
   {
      return stack->array[--stack->top];
   } else 
   {
     printf("Error stack is empty \n");
     return 0xFFFFFFFF;
}



void initQueue(QueueWithStack* queue, int size)
{
  queue->stack1 = malloc(sizeof(Stack));
  queue->stack2 = malloc(sizeof(Stack));
  initStack(stack1,size);
  initStack(stack2, size);
}

void enqueue(QueueWithStack* queue, int data)
{
   push(queue->stack1,data);	
}

int dequeue(QueueWithStack* queue)
{ 
	if(isEmpty(queue->stack1) && isEmpty(queue->stack2))
	{
		printf("Queue empty \n");
		return 0xFFFFFFFF;
	}
	if(isEmpty(queue->stack2))
	{
		while(!isEmpty(queue->stack1))
		{
			int data = pop(queue->stack1);
			push(queue->stack2,data);
		}
	}
	return pop(queue->stack2);


}
  
	

