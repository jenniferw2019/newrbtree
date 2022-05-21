/*
This program allows the user to enter a number into the red black tree with the console or 
read in a string of numbers with a file. 
The user can visualize the tree that shows the number, color, and parent. 
Author: Jennifer Wang
5/5/22
 */
#include "node.h"
#include <fstream>
#include <cstring>
#include <cstdio>
#include <cstdlib>

using namespace std;

int main()
{
  bool runProgram = true;
  char option[20];
  int spaceCount = 0;
  int tokenCount = 0;
  int filelength;
  char* bufferFile;
  int* numberArray;
  node* Tree = NULL;

  while (runProgram == true)
    {
      //ask user to add a number, read in from file, visualize tree, or end program
      cout << "Type ADD, READ, VISUALIZE, QUIT" << endl;
      cin.get(option, 20);
      cin.get();

      //if read, read in number from a file
      if (strcmp(option, "READ") == 0)
	{
	  ifstream file ("file.txt", ifstream::in);
	  if (file)
	    {
	      file.seekg(0, file.end);
	      filelength = file.tellg();
	      file.seekg(0, file.beg);
	      
	      bufferFile = new char[filelength];
	      file.read(bufferFile, filelength);
	      
	      file.close();
	    }
	  else
	    {
	      cout << "no such file named file.txt" << endl;
	    }
	  
	  for (int i = 0; i < filelength; i++)
	    {
	      if (bufferFile[i] == ' ')
		{
		  spaceCount++;
		}
	      tokenCount = spaceCount + 1;
	    }
	  int a = 0;
	  numberArray = new int[tokenCount];
	  char* token;
	  token = strtok(bufferFile, " ");
	  while (token != NULL)
	    {
	      numberArray[a] = atoi(token);
	      token = strtok(NULL, " ");
	      a = a + 1;
	    }

	  //node* newNode = new node();
	  for (int i = 0; i < tokenCount; i++)
	    {
	      node* newNode = new node();
	      newNode->data = numberArray[i];
	      newNode->color = red;
	      insert(Tree, Tree, Tree, newNode);
	      updateTree(Tree, newNode);
	    }
	}

      //if add, add a number in from console
      else if (strcmp(option, "ADD") == 0)
	{	
	  int numInput = 0;
	  cout << "Enter a number" << endl;
	  cin >> numInput;
	  cin.get();
	  node* newNode = new node();
	  newNode->data = numInput;
	  newNode->color = red;
	  
	  insert(Tree, Tree, Tree, newNode);
	  updateTree(Tree, newNode);
	}

      //if visualize, visualize the tree
      else if (strcmp(option, "VISUALIZE") == 0)
	{
	  visualize(Tree, 0);
	}

      //if quit, end program
      else if (strcmp(option, "QUIT") == 0)
	{
	  runProgram = false;
	}
    }
  
}
