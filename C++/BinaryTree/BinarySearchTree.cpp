#include "BinarySearchTree.hpp"
#include <iostream>

// Implement the functions here.
using namespace std;

BinarySearchTree::Node::Node(DataType newval)
{
   	val = newval;
   	left = NULL;
	right = NULL;
   	//assume nothing in the list when the list is first constructed
}


BinarySearchTree::BinarySearchTree()
{
   	root_ = NULL;
	size_ = 0;
}

BinarySearchTree::~BinarySearchTree()
{
  while(root_)
    remove(root_->val);
    
  size_ = 0;
/*  Node* parent = NULL;
  Node* leaf = root_;
  while(root_!=NULL)
  {
    leaf = root_;
    parent = root_;
    if(leaf->left && leaf->right)
    {
        while(!leaf->left && !leaf->right) //Traverse to leaf
        {    
              if(leaf->left)
              {
                  parent = leaf;
                  leaf=leaf->left;
              } 
              if(leaf->right)
              {
                  parent = leaf;
                  leaf=leaf->right;
              }
        }
    }
    
      if(leaf == parent->left)
        parent->left = NULL;
      if(leaf == parent ->right)
        parent->right = NULL;
      delete leaf;
  }
 size_ = 0;
*/
}

unsigned int BinarySearchTree::depth() const
{
    unsigned int depth = (getNodeDepth(root_)-1); cout << depth;
    if(depth >= 0)
      return depth;
    else cout << depth;
}


int BinarySearchTree::getNodeDepth(Node *n) const
{
  if(n == NULL)
    return 0;
    
     int lDepth = getNodeDepth(n->left);
     int rDepth = getNodeDepth(n->right);
     
     if(lDepth <= rDepth)
       return rDepth+1;
     else
       return lDepth+1;
   
  
}

unsigned int BinarySearchTree::size() const
{ 
	return size_;
}

bool BinarySearchTree::insert(DataType val)
{
 Node* temp = root_;
 if(root_ == NULL)
 {
      root_ = new Node(val);
      size_ ++;
      return true;
 }
 //else if(exists(val))
  // return false;
 while(temp!=NULL)
 {
    if(temp->val==val)
      return false;
    if(val < temp->val)
    { 
      if(temp->left==NULL)
      {
        temp->left=new Node(val);
        size_ ++;
        return true;
      }
      temp = temp->left;                 
    }
    if(val > temp->val)
    {
      if(temp->right==NULL)
      {
        temp->right=new Node(val);
        size_ ++;
        return true;
      }  
      temp = temp->right;                 
    }
 }
}
/*
bool BinarySearchTree::insert(DataType val)
{
     Node*newnode = root_;
     Node*newnode2 = new Node(val);
     
     if(root_==NULL)
     {
         root_=newnode2;
         size_++;
         return true;
     }
     
     while(newnode!=NULL)
     {
           
           if(val>newnode->val)
           {
              if(newnode->right==NULL)
              {
                  newnode->right = newnode2;
                  size_=size_+1;
                  return true;
              }
              newnode= newnode->right;
           }
           
           if(val<newnode->val)
           {
              if(newnode->left==NULL)
              {
                 newnode->left = newnode2;
                 size_=size_+1;
                 return true;
              }
              newnode= newnode->left;
           }
           
           if(newnode->val==val)
              return false;
     }
     
      
         
}*/

bool BinarySearchTree::remove(DataType val)
{
     if (!root_)
        return false;
     
     Node* deader = root_;
     Node* parent = root_;
     Node* minParent = root_;
     
     if (!exists(val))
        return false;
     
     if (deader->val == val && !deader->left && !deader->right)
     {
         delete root_;
         root_ = NULL;
         size_ --;
         return true;
     }
     while(val!=deader->val) //locate deader
     {
      
      if(val<deader->val)
      {
        if(deader->left == NULL)
          return false;
        parent = deader;
        deader = deader->left;                 
      }
      else if(val>deader->val)
      {
        if(deader->right == NULL)
          return false;
        parent = deader;
        deader = deader->right;                 
      }
     }  
     if(parent == deader)      //if deader is root node
     {
         if(deader->left==NULL && deader->right==NULL) //if root has no children
        {
          delete deader;
          root_ = NULL;
          size_ --;
          return true;
        }
        else if(deader->left!=NULL && deader->right==NULL) //if root has lchild
        {
          delete deader; 
          root_ = deader -> left;
          size_ --;
          return true;
        }    
        else if(deader->left==NULL && deader->right!=NULL) //if root has rchild
        { 
          delete deader;
          root_ = deader->right;
          size_ --;
          return true;
        }
        else if(deader->left!=NULL && deader->right!=NULL) //if root has 2 children
        {
          Node * min = deader->right;
          while(min->left != NULL)
          {
            minParent = min;
            min = min->left;
          }
          min->left= deader->left;
          if(deader->right!=min)
          {
           min->right = deader->right;
           minParent->left=NULL;
          } 
          delete deader; 
          root_ = NULL;
          size_ --;
          return true;
        }       
     }
     else if(parent->left==deader)  //locate parent with lchild as deader
      {
        if(deader->left==NULL && deader->right==NULL) //if deader is leaf
        {
          parent-> left = NULL;
          delete deader;
          deader = NULL;
          size_ --;
          return true;
        }
        else if(deader->left!=NULL && deader->right==NULL) //if deader has lchild
        {
          parent->left = deader->left;
          delete deader;
          deader = NULL; 
          size_ --;
          return true;
        }    
        else if(deader->left==NULL && deader->right!=NULL) //if deader has rchild
        {
          parent->left = deader->right;
          delete deader; 
          deader = NULL;
          size_ --;
          return true;
        }
        else if(deader->left!=NULL && deader->right!=NULL) //if deader has 2 children
        {
          Node * min = deader->right;
          while(min->left != NULL)
            min = min->left;
          parent->left = min;
          parent->left->left = deader->left;
          if(parent->left!=deader->right)
           parent->left->right = deader->right;
          delete deader; 
          deader = NULL;
          size_ --;
          return true;
        }                       
      }
      else if(parent->right==deader) //locate parent with rchild as deader
      {
        if(deader->left==NULL && deader->right==NULL) //if deader is leaf
        {
          parent-> right = NULL;
          delete deader;
          deader = NULL;
          size_ --;
          return true;
        }        
        else if(deader->left==NULL && deader->right!=NULL) //if deader has lchild
        {
          parent->right = deader->left;
          delete deader; 
          deader = NULL;
          size_ --;
          return true;
        }    
        else if(deader->left!=NULL && deader->right==NULL) //if deader has rchild
        {
          parent->right = deader->right;
          delete deader; 
          deader = NULL;
          size_ --;
          return true;
        }
        else if(deader->left!=NULL && deader->right!=NULL) //if deader has 2 children
        {
          Node * min = deader->right;
          while(min->left != NULL)
          {
            minParent = min;
            min = min->left;
          }
          parent->right = min;
          parent->right->left = deader->left;
          if(parent->right!=deader->right)
          {
           parent->right->right = deader->right;
           minParent->left = NULL;
          }
          else
          {
           minParent->right = NULL;
          }
          delete deader; 
          deader = NULL;
          size_ --;
          return true;
        }                      
      }
}

bool BinarySearchTree::exists(DataType val) const
{
 if (!root_)
  return false;  
 Node *temp = root_;
 {
  while(temp!=NULL)
  {
    if(val==temp->val)
      return true;
    if(val<temp->val)
    {
      temp = temp->left;                 
    }
    else if(val>temp->val)
    {
      temp = temp->right;                 
    }
  }
  return false;
 }
}
BinarySearchTree::DataType BinarySearchTree::min() const
{
 Node *min = root_;
 while(min->left != NULL)
  min = min->left;
 return min->val;
}

BinarySearchTree::DataType BinarySearchTree::max() const
{
 Node *max = root_;
 while(max->right != NULL)
  max = max->right;
 return max->val;	
}

void BinarySearchTree::print() const
{
     
}
