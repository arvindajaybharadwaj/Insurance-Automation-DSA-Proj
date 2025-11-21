#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

BST *create_node()
{
    BST *new = (BST *)malloc(sizeof(BST));
    if (new == NULL)
    {
        printf("Memory could not be allocated!\n");
        exit(0);
    }
    printf("Enter Your Name: ");
    scanf("%s", new->name);

    // Validate Age
    while (1)
    {
        printf("Enter Your Age (integer): ");
        if (scanf("%d", &new->age) != 1)
        {
            printf("Invalid input! Please enter a valid number.\n");
            while (getchar() != '\n')
                ;
            continue;
        }
        if (new->age < 18 || new->age > 120)
        {
            printf("Age must be between 18 and 120.\n");
            continue;
        }
        break;
    }

    printf("Enter Your ID: ");
    scanf("%d", &new->Id);

    // Validate Phone Number
    while (1)
    {
        printf("Enter your Phone Number (10 digits): ");
        if (scanf("%lld", &new->phonenumber) != 1)
        {
            printf("Invalid input! Please enter a valid number.\n");
            while (getchar() != '\n')
                ;
            continue;
        }
        if (new->phonenumber < 1000000000LL || new->phonenumber > 9999999999LL)
        {
            printf("Phone number must be exactly 10 digits.\n");
            continue;
        }
        break;
    }

    // Validate Email
    while (1)
    {
        printf("Enter Your Email ID: ");
        scanf("%s", new->email);
        char *atSign = strchr(new->email, '@');
        char *dot = strchr(new->email, '.');
        if (atSign != NULL && dot != NULL && atSign < dot && strlen(new->email) > 5)
        {
            break;
        }
        printf("Invalid email format! Email must contain '@' and '.' with valid structure.\n");
    }

    new->left = new->right = NULL;
    return new;
}

BST *addBST(BST **root)
{
    BST *temp = create_node();
    if (!*root)
    {
        *root = temp;
        return temp;
    }
    BST *loop = *root, *parent = NULL;
    while (loop)
    {
        parent = loop;
        if (temp->Id < loop->Id)
            loop = loop->left;
        else if (temp->Id > loop->Id)
            loop = loop->right;
        else
        {
            free(temp);
            printf("The Value of ID already exists!\n");
            return NULL;
        }
    }
    if (temp->Id < parent->Id)
        parent->left = temp;
    else
        parent->right = temp;
    return temp;
}

void inorderBST(BST *root)
{
    if (root)
    {
        inorderBST(root->left);
        printf("Name: %s\n", root->name);
        printf("Age: %d\n", root->age);
        printf("Id: %d\n", root->Id);
        printf("Phone Number: %lld\n", root->phonenumber);
        printf("Email: %s\n", root->email);
        printf("-------------------------------------------\n");
        inorderBST(root->right);
    }
}

bool removeBST(BST **root, int id)
{
    BST *temp = *root, *parent = NULL;
    while (temp && temp->Id != id)
    {
        parent = temp;
        if (id < temp->Id)
            temp = temp->left;
        else
            temp = temp->right;
    }
    if (!temp)
    {
        printf("Element not found!\n");
        return false;
    }

    if (!temp->left && !temp->right)
    {
        if (!parent)
            *root = NULL;
        else if (parent->left == temp)
            parent->left = NULL;
        else
            parent->right = NULL;
        free(temp);
    }
    else if (!temp->left || !temp->right)
    {
        BST *child = temp->left ? temp->left : temp->right;
        if (!parent)
            *root = child;
        else if (parent->left == temp)
            parent->left = child;
        else
            parent->right = child;
        free(temp);
    }
    else
    {
        BST *succParent = temp, *succ = temp->right;
        while (succ->left)
        {
            succParent = succ;
            succ = succ->left;
        }
        temp->Id = succ->Id;
        strcpy(temp->name, succ->name);
        temp->age = succ->age;
        temp->phonenumber = succ->phonenumber;
        strcpy(temp->email, succ->email);
        if (succParent->left == succ)
            succParent->left = succ->right;
        else
            succParent->right = succ->right;
        free(succ);
    }
    printf("Element deleted!\n");
    return true;
}
