#include <stdio.h>
#include <stdlib.h>
#include <util.h>
#include <limits.h>

//http://cslibrary.stanford.edu/110/

 
typedef struct Node
{
  int data;
  struct Node* left;
  struct Node* right;
}Node;

void printPathRecursive(Node* node, int path[], int length);
int isBSTRecursive(Node* node, int min, int max);

//BST
int lookup(Node* node, int data)
{
    if(node==NULL)
    {
	return 0;
    }
    if(node->data == data)
    {
	return 1;
    }
    if(node->data> data)
    {
	return lookup(node->left,data);
    } else
    {
	return lookup(node->right, data);
    }
 #if 0
  while(node!=NULL and node->data!=data)
  {
	if(data<node->data)
          node = node->left;
        else node = node->right;
   }
   return node
 #endif
}

//BT
int size(Node* node)
{
   if(node ==NULL)
   {
	return 0;
   } else
   {
	return size(node->left)+ size(node->right) +1;
   }
}

//BT
int maxDepth(Node* node)
{
   if(node ==NULL)
   {
	return 0;
   } else
   {
	int depthLeft = maxDepth(node->left);
        int depthRight = maxDepth(node->right);
        return depthLeft>depthRight?depthLeft+1:depthRight+1;
   }
}

//BST
void printTree(Node* node)
{

   if(node ==NULL)
   {
	return;
   }
   printTree(node->left);
   printf(" %d ",node->data);
   printTree(node->right);

}


//BT
int hasPathWithSum(Node* node, int sum)
{
  if(node == NULL)
  {
	return sum ==0;
  }
  return hasPathWithSum(node->left, sum- (node->data)) ||
		hasPathWithSum(node->right, sum- (node->data));
}



void printPaths(Node* rootNode)
{
	int path[1000];
        printPathRecursive(rootNode, path, 0);
}
void printPathRecursive(Node* node, int path[], int length)
{
  if(node == NULL)
	return;
  path[length] = node->data;
  length++;
  if(node->left == NULL && node->right == NULL)
  {
	printArray(path, length);
  } else
  {
	printPathRecursive(node->left, path, length); 
	printPathRecursive(node->right, path, length); 
  }
}

int isBST(Node* node)
{
  return isBSTRecursive(node, INT_MIN, INT_MAX);
}

int isBSTRecursive(Node* node, int min, int max)
{
	if(node == NULL)
	 return 1;
        if(node->data < min || node->data > max)
         return 0;
        return isBSTRecursive(node->left, min, node->data) && isBSTRecursive(node->right, node->data+1, max);
}


Node* minimumNode(Node* node)
{
   if(node == NULL)
	return NULL;
   while(node->left != NULL)
   {
	node = node->left;
   }
   return node;
}

		

/*
n-node binary tree, track the left most child and right sibling
*/

Node* newNode(int data)
{
	Node* newNode = malloc(sizeof(Node));
        newNode->data = data;
	newNode->left = newNode->right = NULL;
	return newNode;
}

Node* insert(Node* root, int data)
{

	if(root == NULL)
		return newNode(data);
 	else
	{
		if(data <= root->data)
			root->left = insert(root->left, data);
		else 
			root->right = insert(root->right, data);
	}
	return root;
}


Node* deleteNode(Node* node, int data)
{
    if(node == NULL)
	return node;
    
    if(data < node->data)
    {
	node->left = deleteNode(node->left, data);
    } else if (data > node->data)
    {
	node->right = deleteNode(node->right, data);
    }else
    {
	//We found the node to be deleted
  
	//If either of the children are NULL promote the other 
        if(node->left == NULL)
        {
           Node* temp = node->right;
           free(node);
       	   return temp;
        } 
        if(node->right == NULL)
        {
           Node* temp = node->left;
           free(node);
       	   return temp;
        }
	//temp is basically the next element in the sorted order to node
        // it is the left most node on the right branch.  This left can have a right child, so its delete has to be done using deleteNode
        Node *temp = minimumNode(node->right);
        node->data = temp->data;
        node->right = deleteNode(node->right, temp->data);
    }
    return node;
}	
     
	
  
