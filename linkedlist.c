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

void append(Node** firstRef, Node** secondRef)
{
    if(*firstRef == NULL)
    {
      *firstRef = *secondRef;
    } else 
    {
	Node* current = *firstRef;
        while(current->next != NULL)
        {
	   current = current->next;
	}
	current->next = *secondRef;	
    }
    *secondRef = NULL;
}

void moveNode(Node** dest, Node** source)
{
   //Move the node from front of source to front of dest
   Node* node = *source;
   *source = node->next;
   node->next=*dest;
   *dest = node;
}

void splitIntoTwo(Node* input, Node** front,Node** back)
{
  if(input ==NULL || input->next == NULL)
  {
    *front = input;
    *back = NULL;
  } else 
  {
	Node* slow =input;
        Node* fast = input->next;
        while(fast!=NULL)
        {
	   fast = fast->next;
           if(fast!=NULL)
           {
		fast = fast->next;
		slow = slow->next;
	   }
	}
	*front = input;
        *back = slow->next;
        slow->next = NULL;
  }
}

Node* sortedMerge(Node* first, Node* second)
{
	Node* result = NULL;
	Node** lastRef = &result;
        while(1)
	{
		if(first == NULL)
		{
			*lastRef = second;
			break;
		}else if(second == NULL)
		{
			*lastRef = first;
			break;
		}else
		{
			if(first->data <= second->data)
			{	
				moveNode(lastRef,&first);
			}else {
				moveNode(lastRef, &second);
			}
			lastRef = &((*lastRef)->next);
		}
         }
	 return result;
}

void reverse(Node** head)
{
#if 0
while (current != NULL) {
next = current->next; // tricky: note the next node
current->next = result; // move the node onto the result
result = current;
current = next;
}
*head = result

#endif

    if(*head== NULL)
    {
	return;
    }
    Node* first = *head;
    Node* rest = first->next;
    if(rest == NULL)
    {
	return;
    }
    reverse(&rest);
    first->next->next = first;
    first->next = NULL;
    *head = rest; 
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
    append(&node, &copy);
    printLinkedList(node);
    reverse(&node);
    printLinkedList(node);
 
    
}
   
   

/*
 Binary tree to double linked list in order  (Node-data,small, large... recursiveBuildList(Node*) { recu(node.small), recu(node.lar), node.small = node.large = node;  append(node.small, node, node.large}
append means joining a large to b small and a a small to blarge and vice versa
*/ 
