#include <stdio.h>
#include <stdlib.h>
#include <util.h>


//http://cslibrary.stanford.edu/110/

 
typedef struct Node
{
  int data;
  struct Node* left;
  struct Node* right;
}Node;


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


int hasPathWithSum(Node* node, int sum)
{
  if(node == NULL)
  {
	return sum ==0;
  }
  return 

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
void printPathRecursive(Node* node, int path[], length)
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


/*
n-node binary tree, track the left most child and right sibling
*/
