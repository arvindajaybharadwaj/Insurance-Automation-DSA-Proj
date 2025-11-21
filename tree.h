#ifndef TREE_H
#define TREE_H
#include <stdbool.h>

typedef struct tree
{
    char name[400];
    int Id;
    int age;
    long long phonenumber;
    char email[500];
    struct tree *left, *right;
} BST;

bool addBST(BST **root);
void inorderBST(BST *root);
bool removeBST(BST **root, int id);

#endif
