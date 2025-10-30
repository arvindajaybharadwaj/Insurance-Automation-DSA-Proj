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
    printf("Enter Your  Name:");
    scanf("%s",&temp->name);
    printf("Enter Your Age:");
    scanf("%d",&temp->age);
    printf("Enter Your ID:");
    scanf("%d",&temp->Id);
    printf("Enter your Phone Number:");
    scanf("%d",&temp->phone_number);
    printf("Enter Your Email ID:");
    scanf("%s",&temp->email);
    BST *loop=root;
    BST *parent = NULL;

    while(loop != NULL)
    {
        parent = loop;
        if(temp->Id < loop->Id)
        {
            loop = loop->left;
        }
        else if(temp->Id > loop->Id)
        {
            loop = loop->right;
        }
        else if(temp->Id == loop->Id)
        {
            free(temp);
            printf("The Value of ID already exists!");
            return false;
        }
    }

    if(temp->Id < parent->Id)
    {
        parent->left = temp;
    }
    else
    {
        parent->right = temp;
    }
    
    return true;
};
void inorder(BST *root)
{
    BST* temp=root;
    inorder(temp->left);
    printf("Name is %s\n",temp->name);
    printf("Age is %d\n",temp->age);
    printf("Id is %d",temp->Id);
    printf("Phone Number is %d",temp->phone_number);
    printf("Email is %d",temp->email);
    inorder(temp->right);

};

bool remove (BST *root)
{
    
};

