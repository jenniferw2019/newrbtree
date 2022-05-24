//header file for node
#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

enum nodeColor {black, red};
enum nodeDir {Right, Left};

struct node
{
  //variables
  int data;
  nodeColor color;
  node* parent;
  node* left;
  node* right;
  
};

//function prototypes
void insert(node* &root, node* parent, node* current, node* newNode);
void print(node* root);
void visualize(node* root, int level);
node* search(node* root, node* parent, node* current, int searchNum);
node* getParent(node* root, node* current, node* previous, node* lookParent);
void treeRotationRight(node* &root,node* subRoot);
void treeRotationLeft(node* &root, node* subRoot);
void updateTree(node* &root, node* n);
node* maximum(node* root);
void deleteNode(node* root, int insertData);
nodeDir getDirection(node* cnode);
node* getSibling(node* pnode, nodeDir cdirect);
node* getCNephew(node* snode, nodeDir cdirect);
node* getDNephew(node* snode, nodeDir cdirect);

#endif
