//cpp for node
#include "node.h"
#include <iostream>

using namespace std;

//create red black tree / insert value into tree
void insert(node* &root, node* parent, node* current, node* newNode)
{
  //new value becomes root of tree
  if (root == NULL)
    {
      root = newNode;
      root->parent = NULL;
      root->left = NULL;
      root->right = NULL;
    }
  //adding value to end of tree
  else if (current == NULL)
    {
      newNode->left = NULL;
      newNode->right = NULL;
      current = newNode;
      if (newNode->data < parent->data)
	{
	  parent->left = current;
	  current->parent = parent;
	}
      else
	{
	  parent->right = current;
	  current->parent = parent;
	}
      
    }
  else
    {
      parent = current;
      if (newNode->data < current->data)
	{
	  current = current->left;
	}
      else
	{
	  current = current->right;
	}
      insert(root, parent, current, newNode);
    }
}

//print redblack tree numbers from smallest to largest
void print(node* root)
{
  if (root != NULL)
    {
      print(root->left);
      cout << root->data << " ";
      print(root->right);
    }
}

//visualize red black tree
void visualize(node* root, int level)
{
  if (root != NULL)
    {
      visualize(root->right, level + 1);
      for (int i = 0; i < level; i++)
	{
	  cout << '\t';
	}
      cout << root->data;
      if (root->color == black)
	{
	  cout << "(B)";
	}
      else
	{
	  cout << "(R)";
	}
      cout << "|";
      if (root->parent != NULL)
	{
	  cout << (root->parent)->data << endl;
	}
      else
	{
	  cout << endl;
	}
      visualize(root->left, level + 1);
    }
}

//search for a specific value in tree
node* search(node* root, node* parent, node* current, int searchNum)
{
  if (current == NULL)
    {
      return NULL;
    }
  else if (current->data == searchNum)
    {
      return current;
    }
  else
    {
      parent = current;
      if (parent->data < searchNum)
	{
	  current = current->right;
	}
      else
	{
	  current = current->left;
	}
      return search(root, parent, current, searchNum);
    }
}

//find parent of a node
node* getParent(node* root, node* current, node* previous, node* lookParent)
{
  if (root == lookParent)
    {
      return NULL;
    }
  else if (current == lookParent)
    {
      return previous;
    }
  else
    {
      previous = current;
      if(previous->data < lookParent->data)
	{
	  current = current->right;
	}
      else
	{
	  current = current->left;
	}
      return getParent(root, current, previous, lookParent);
    }
}

//rotate to the right
void treeRotationRight(node* &root, node* subRoot)
{
  node* rootParent = subRoot->parent;
  node* leftChild = subRoot->left;
  node* grandChild;
  if (leftChild != NULL)
    {
      grandChild = leftChild->right;
    }
  
  subRoot->left = grandChild;
  if (grandChild != NULL)
    {
      grandChild->parent = subRoot;
    }

  leftChild->right = subRoot;
  subRoot->parent = leftChild;

  if (rootParent != NULL)
    {
      if (rootParent->right == subRoot)
	{
	  rootParent->right = leftChild;
	  leftChild->parent = rootParent;
	}
      else
	{
	  rootParent->left = leftChild;
	  leftChild->parent = rootParent;
	}
    }
  else
    {
      root = leftChild;
      root->parent = NULL;
    }
}

//rotate to the left
void treeRotationLeft(node* &root, node* subRoot)
{
  node* rootParent = subRoot->parent;
  node* rightChild = subRoot->right;
  node* grandChild;
  if (rightChild != NULL)
    {
      grandChild = rightChild->left;
    }

  //start rotating
  subRoot->right = grandChild;
  if (grandChild != NULL)
    {
      grandChild->parent = subRoot;
    }

  rightChild->left = subRoot;
  subRoot->parent = rightChild;

  if (rootParent != NULL)
    {
      if (rootParent->left == subRoot)
	{
	  rootParent->left = rightChild;
	  rightChild->parent = rootParent;
	}
      else
	{
	  rootParent->right = rightChild;
	  rightChild->parent = rootParent;
	}
    }
  else
    {
      root = rightChild;
      root->parent = NULL;
    }
}

//update tree with different cases
void updateTree(node* &root, node* n)
{
  node* parent;
  node* grandParent;
  node* uncle;
  node* child;

  if (n == root)
    {
      n->color = black;
    }
  else // n!= root
    {
      do {
	parent = n->parent;
	if (parent->color == black) // case 1: parent color is black
	  {
	    return;
	  }
	else //parent color == red
	  {
	    grandParent = parent->parent;
	    if (grandParent == NULL) // case 2: parent is red root
	      {
		parent->color = black;
		return;
	      }
	    else //grandparent != NULL
	      {
		if (parent == grandParent->left)
		  {
		    uncle = grandParent->right;
		  }
		else
		  {
		    uncle = grandParent->left;
		  }
		if (uncle != NULL && uncle->color == red) // case 3: parent and uncle are red
		  {
		    parent->color = black;
		    uncle->color = black;
		    grandParent->color = red;
		    n = grandParent;
		    parent = n->parent;
		  }
		else //case 5 and 6: uncle is NULL or black
		  {
		    if (parent == grandParent->left) // case 5: parent is left of grandparent
		      {
			if (n == parent->right) //in line grandparent
			  {
			    treeRotationLeft(root, parent);
			    node* temp = n;
			    n = parent;
			    parent = temp;
			  }
			treeRotationRight(root, grandParent); // out line grandparent
			parent->color = black;
			grandParent->color = red;
			return;
		      }
		    else // case 6: parent is right of grandparent
		      {
			
			if (n == parent->left) // in line grandparent
			  {
			    treeRotationRight(root, parent);
			    node* temp = n;
			    n = parent;
			    parent = temp;
			  }
			treeRotationLeft(root, grandParent); //out line grandparent
			parent->color = black;
			grandParent->color = red;
			return;
		      }
		    
		  } //uncle is NULL or black
	      }//grandparent != NULL
	    
	  } //parent color == red
	
      } while (parent != NULL);

      root->color = black; // case 4: n ia red root
      
    } // n!= root
}

node* maximum(node* root)
{
  if (root->right != NULL)
    {
      root = root->right;
      return maximum(root);
    }
  else
    {
      return root;
    }
}

nodeDir getDirection(node* cnode)
{
  node* nodeparent = cnode->parent;
  if (cnode == nodeparent->left)
    {
      return Left;
    }
  else
    {
      return Right;
    }
}

node* getSibling(node* pnode, nodeDir cdirect) //current node direction
{
  if (cdirect == Left)
    {
      return pnode->right;
    }
  else
    {
      return pnode->left;
    }
}

node* getCNephew(node* snode, nodeDir cdirect) //current node direction
{
  if (cdirect == Left)
    {
      return snode->left;
    }
  else
    {
      return snode->right;
    }
}

node* getDNephew(node* snode, nodeDir cdirect)
{
  if (cdirect == Left)
    {
      return snode->right;
    }
  else
    {
      return snode->left;
    }
}

void deleteNode(node* &root, int deleteData)
{
  node* cparent; //current node's parent
  node* sibling; //current node's sibling
  node* cNephew; //current node's close nephew
  node* dNephew; //current node's distant nephew
  node* gparent; //current node's grandparent
  node* delnode; //current node (need to delete)
  delnode = search(root, root, root, deleteData);
  if (delnode == NULL)
    {
      cout << "number is not in tree" << endl;
    }
  else // found number in tree
    {
      //if del node has both children, find predecessor, replace delnode value with predecessor value
      //set delnode as precedessor, now delnode has at most 1 child (either no childre, or only 1 child)
      if (delnode->left != NULL && delnode->right != NULL)
	{
	  node* predecessor = maximum(delnode->left);
	  delnode->data = predecessor->data;
	  delnode = predecessor;
	}
      
      //delnode has 1 child
      if (delnode->right != NULL && delnode->left == NULL) //right child
	{
	  delnode->data = (delnode->right)->data;
	  node* temp = delnode->right;
	  delnode->right = NULL;
	  temp->parent = NULL;
	  delete temp;
	}
      else if (delnode->right == NULL && delnode->left != NULL) //left child
	{
	  delnode->data = (delnode->left)->data;
	  node* temp = delnode->left;
	  delnode->left = NULL;
	  temp->parent = NULL;
	  delete temp;
	}
      else //no children
	{
	  if (delnode->color == red)
	    {
	      nodeDir deldirect = getDirection(delnode);
	      cparent = delnode->parent;
	      if (deldirect == Left)
		{
		  cparent->left = NULL;
		}
	      else //deldirect == Right
		{
		  cparent->right = NULL;
		}
	      delnode->parent = NULL;
	      delete delnode;
	    }
	  else //delnode is black given no children;
	    {
	      //delete root
	      if (root == delnode)
		{
		  root = NULL;
		  delete delnode;
		  return;
		}
	      cparent = delnode->parent;
	      nodeDir direct = getDirection(delnode);
	      
	      if (delnode == cparent->left) //left child
		{
		  cparent->left = NULL;
		  delnode->parent = NULL;
		  delete delnode;
		}
	      else
		{
		  cparent->right = NULL;
		  delnode->parent = NULL;
		  delete delnode;
		}

	      //update red black tree

	      do {
		sibling = getSibling(cparent, direct);
		cNephew = getCNephew(sibling, direct);
		dNephew = getDNephew(sibling, direct);
	    	
		if (sibling->color == red) //case 3: sibling color is red. parent, cNephew, dNephew are black
		  {
		    if (direct == Left)
		      {
			treeRotationLeft(root, cparent);
		      }//direction left
		    
		    else //direction right
		      {
			treeRotationRight(root, cparent);
		      }
		    cparent->color = sibling->color;
		    sibling->color = black;
		    sibling = cNephew;
		    cNephew = getCNephew(sibling, direct);
		    dNephew = getDNephew(sibling, direct);
		  }//sibling is red

		if (dNephew != NULL && dNephew->color == red) //case 6: distant nephew is red, sibling is black
		  {
		    
		    if (direct == Left)
		      {
			treeRotationLeft(root, cparent);
		      }
		    else
		      {
			treeRotationRight(root, cparent);
		      }
		    sibling->color = cparent->color;
		    cparent->color = black;
		    dNephew->color = black;
		    return;
		  }

		if (cNephew != NULL && cNephew->color == red) //case 5: sibling is black,
		  //distant nephew is black, close nephew is red
		  {
		    if (direct == Left)
		      {
			treeRotationRight(root, sibling);
		      }
		    else
		      {
			treeRotationLeft(root, sibling);
		      }
		    sibling->color = red;
		    cNephew->color = black;
		    dNephew = sibling;
		    sibling = cNephew;
		    //fall through to case 6
		    if (direct == Left)
		      {
			treeRotationLeft(root, cparent);
		      }
		    else
		      {
			treeRotationRight(root, cparent);
		      }
		    sibling->color = cparent->color;
		    cparent->color = black;
		    dNephew->color = black;
		    return;
		  }

		if (cparent->color == red) //case 4: if parent is red, sibling, dNephew, cNephew are all black
		  {
		    sibling->color = red;
		    cparent->color = black;
		    return;
		  }//parent is red

		//case 1: parent, sibling, cNephew, dNephew are all black
		sibling->color = red;
		delnode = cparent;
		cparent = delnode->parent;

		if (cparent != NULL)
		  {
		    direct = getDirection(delnode);
		  }
	      } while (cparent != NULL);
	      
	      return; //case 2: update complete
	      
	    }//delnode is black
	}//no children
    }//else, found number in tree
}
