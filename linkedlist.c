#include <stdio.h>
#include <stdlib.h>
#include <util.h>


//http://cslibrary.stanford.edu/103/

 
typedef struct Node
{
  int data;
  struct Node* next;
}Node;



int length(Node* node)
{
  int length =0;
  while(node !=NULL)
  {
     node = node->next;
     length++;
  }
  return length;
}


void push(Node** nodeRef, int data)
{
  Node* currentNode = *nodeRef;
  Node* newNode = malloc(sizeof(Node));
  newNode->data = data;
  newNode->next = currentNode;
  *nodeRef = newNode;
}



void printLinkedList(Node* node)
{
  printf("The linkedList is {");
  while(node !=NULL)
  {
     printf("%d ",node->data);
     node = node->next;
  }
  printf("}\n");


}


Node* buildAtHead()
{
   //Build a linked list from front, like a stack
   Node*  head = NULL; 
   int i =0;
   while(i<5)
   {
      push(&head,i);
      i++;
   } 
   int listLength = length(head);
   printf("The linked list length is %d \n",listLength);
   return head;
}


Node* buildAtTail()
{
 // Append elements at the end. Alternative is to have a separate case for adding the first node
 // Node* head; push(&head) Node* tail = head;  while( push((&tail->next)   tail = tail->next)
#if 0
  Node dummyNode;
  Node* tail = &dummyNode;
  tail->next = NULL;
  int i =0;
  while(i<5)
  {
     push(&(tail->next),i);
     tail = tail->next;
     i++;
  }
  printLinkedList(dummyNode.next);
#endif
  Node* head = NULL;
  Node** lastPtrRef = &head;
  int i =0;
  while (i<5)
  {
     push(lastPtrRef,i);
     lastPtrRef = &((*lastPtrRef)->next);
     i++;
  }
  return head;
}

void appendNode(Node** node, int data)
{

	Node* current = *node;
	if(current == NULL)
	{
		push(node,data);
	}else 
	{   
		while(current->next !=NULL)
		{
			current = current->next;
		}
		push( &(current->next),data);	
	}

}

Node* copyList(Node* originalList)
{
   Node* newList = NULL;
   Node** localRefPtr = &newList;
   while(originalList != NULL)
   {
	push(localRefPtr, originalList->data);
        localRefPtr =  &((*localRefPtr)->next);
        originalList = originalList->next;
   }
   return newList;
}

void deleteList(Node* node)
{
  while(node!=NULL)
  {
    Node* temp = node;
    node = node->next;
    free(temp);
  }
}

int pop(Node** node)
{
  Node* top = *node;
  int data = top->data;
  *node = top->next;
  free(top);
  return data;
}

void insertAtIndex(Node** headRef, int index, int data)
{
	#if 0 
        Node* currentNode = *headRef;
        if(index == 0)
        {
	    push(node, data);
 	    return;
        }
         int count =0;
	while(count <index-1)
	{
		currentNode = currentNode->next;	  
		count++;
	}
	push(&(currentNode->next),data);
        #endif

    int count =0;
    while(count<index)
    {
	headRef = &((*headRef)->next);
        count++;
    }
    push(headRef,data);
 
}

void sortedInsert(Node** headRef, Node* newNode)
{
  
    while(*headRef!=NULL && (*headRef)->data < newNode->data)
    {
	headRef = &((*headRef)->next);
    }
    newNode->next = *headRef;
    *headRef = newNode;

}

void insertSort(Node** headRef)
{
  Node* currentHead = *headRef;
  Node* result = NULL;
  Node* next = NULL;
  while(currentHead != NULL)
  {
     next = currentHead->next;
     sortedInsert(&result, currentHead);
     currentHead = next;
  }
  *headRef = result; 

}


int main(int argc, char* argv[])
{
    Node* node = buildAtHead();
    printLinkedList(node);
    pop(&node);
    printLinkedList(node);
    deleteList(node);
    node = buildAtTail();
    printLinkedList(node);
    Node* copy = copyList(node);
    printLinkedList(copy);
    appendNode(&node, 5);
    appendNode(&copy, 6);
    printLinkedList(node);
    printLinkedList(copy);
    insertAtIndex(&node,0,77);
    insertAtIndex(&node, 3, 33);
    insertAtIndex(&node, 7,99);
    insertAtIndex(&node, 9,8);
    printLinkedList(node);
    insertSort(&node);
    printLinkedList(node);
    
}
   
   

 
