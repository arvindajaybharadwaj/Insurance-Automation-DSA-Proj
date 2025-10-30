/* The following functions needs to be implemented 
1. delete 
2.  all the types of display
3. adding
*/
#include<stdbool.h>
#include<stdio.h>
#include"tree.h"
#include<stdlib.h>


BST * create_node()
{
    BST *new=malloc(sizeof(BST));
    if(new==NULL)
    {
        printf("Memory could not be allocated\n");
        exit(0);
    }
    return new;

};

bool add(BST *root)
{
    BST *temp=create_node();
    char 
    printf("Enter the Name:");
    

    if(root==NULL)
    {
        
    }
};

void inorder(BST *root);

bool remove (BST *root);

