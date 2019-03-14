/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			bst.cpp
 * Author(s):		Peter Bauer
 * Due Date:		May 31, 2017
 *-----------------------------------------------------------------------------
 * Description:
 * <your description here>
 *-----------------------------------------------------------------------------
*/
#include "bst.h"
#include <stdlib.h>
#include "general.h"

struct Node *create_new_node(int value);

struct Node
{
  int value;
  struct Node* right;
  struct Node* left;
};

Bst new_bst()
{
  Bst bst=0;
  return bst;
}

void delete_bst(Bst bst)
{
  if(bst==0)return;
  delete_bst(bst->right);
  delete_bst(bst->left);
  sfree(bst);
}


int get_depth(Bst bst)
{
  if (bst==0) return 0;
  int right=get_depth(bst->right);
  int left=get_depth(bst->left);
  if(left <= right)
  {
    return right+1;
  }
  else
  {
    return left+1;
  }
  return 2;
}

struct Node* create_new_node(int value)
{
  Node* newNode=(struct Node*)malloc(sizeof(struct Node));
  newNode->value=value;
  newNode->right=0;
  newNode->left=0;
  return newNode;
}

void add(Bst* bst, int value)
{
  if (*bst==0)
  {
    (*bst)=create_new_node(value);
    return;
  }
  if(value<=(*bst)->value)
  {
    if((*bst)->left==0)
    {
      (*bst)->left=create_new_node(value);
      return;
    }
    add(&(*bst)->left,value);
  }
  else if(value>(*bst)->value)
  {
   if((*bst)->right==0)
    {
      (*bst)->right=create_new_node(value);
      return;
    }
  add(&(*bst)->right,value);
  }
}

int root_value(Bst bst)
{
  if(bst==0) return 0;
  return bst->value;
}


Bst left_subtree(Bst root)
{
  if (root==0) return 0;
  return root->left;
}

Bst right_subtree(Bst root)
{
  if (root==0) return 0;
  return root->right;
}

int traverse_pre_order(Bst bst, int *elements, int start)
{
  if(bst!=0)
  {
    elements[start] = bst->value;
    start++;
    start = traverse_pre_order(bst->left, elements, start);
    start = traverse_pre_order(bst->right, elements, start);
  }
  return start;
}

int traverse_in_order(Bst bst, int *elements, int start)
{
  if(bst != 0)
  {
    start = traverse_in_order(bst->left, elements, start);
    elements[start] = bst->value;
    start++;
    start = traverse_in_order(bst->right, elements, start);
  }
  return start;

}

int traverse_post_order(Bst bst, int *elements, int start)
{
  if(bst!=0)
  {
    start = traverse_post_order(bst->left, elements, start);
    start = traverse_post_order(bst->right, elements, start);
    elements[start] = bst->value;
    start++;
  }
  return start;
}

bool are_equal(Bst bst1, Bst bst2)
{
  if (bst1==0) return bst2==0;
  if (get_depth(bst1)==get_depth(bst2))
  {
    if (bst1->value==bst2->value)
    {
      return are_equal(bst1->left,bst2->left)&&are_equal(bst1->right,bst2->right);
    }
  }
  return false;
}

void most_left_longest_branch(Bst bst, Bst* branch)
{
  if(bst != 0)
  {
    if(get_depth(bst->left) < get_depth(bst->right))
    {
      add(branch, bst->value);
      most_left_longest_branch(&(*bst->right), branch);
    }
    else if(get_depth(bst->left) >= get_depth(bst->right))
    {
      add(branch, bst->value);
      most_left_longest_branch(&(*bst->left), branch);
    }
  }
}

int get_number_of_subtrees(Bst bst)
{
  if (bst != 0)
  {
    int *elements = new int[get_depth(bst)];
    return traverse_pre_order(bst, elements, 0) -1;
  }
  return -1;
}
