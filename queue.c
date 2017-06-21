#include <stdio.h>
#include <stdlib.h>
#include <util.h>

typedef struct Queue
{
 int* array;
 int head;
 int tail;
 int queueLength;
 int queueSize;
}Queue;

typedef struct StackWithQueue
{
   Queue* queue1;
   Queue* queue2;
}StackWithQueue;

void initQueue(Queue* queue, int size)
{
    queue->array = malloc(size* sizeof(int));
    queue->head=0;
    queue->tail=0;
    queue->queueLength = size;
    queue->queueSize =0;
}

int isEmpty(Queue* queue)
{
   return !queue->queueSize;
}

int isFull(Queue* queue)
{
   return (queue->queueLength ==queue->queueSize ? 1:0);
}


void enqueue(Queue* queue, int data)
{
	if(isFull(queue))
	{
		printf("Queue is full \n");
		return;
	}

	queue->array[queue->tail++] = data;
        queue->queueSize++;
	if(queue->tail == queue->queueLength)
	{
		queue->tail = 0;
	}
}

int dequeue(Queue* queue)
{
	if(isEmpty(queue))
	{
		printf("Queue is empty \n");
		return 0xFFFFFFFF;
	}
	int result = queue->array[queue->head++];
        queue->queueSize--;
	if(queue->head == queue->queueLength)
	{
		queue->head = 0;
	}
        return result;
}
  
	
void initStack(StackWithQueue* stack, int size);
{
    stack->queue1 = malloc(sizeof(StackWithQueue));
    stack->queue2 = malloc(sizeof(StackWithQueue));
    initQueue(stack->queue1, size);
    initQueue(stack->queue2, size);
}

void push(StackWithQueue* stack, int data)
{
   if(!isFull(stack->queue1))
   {
	enqueue(stack->queue1,data);
    }
}

int  pop(StackWithQueue* stack)
{
    int result;
    while(!isEmpty(stack->queue1))
    {
	result = dequeue(stack->queue1);
    }
    Queue* temp = stack->queue1;
    stack->queue1 = stack->queue2;
    stack->queue2 = temp;
    return result;

}

