
//the bst is based on their id
typedef struct tree
{
    char name[400];
    int Id;
    int age;
    int phone_number;
    char email[500];
    struct tree *left;
    struct tree *right;
}BST;

bool add(BST *);

void inorder(BST *);

bool remove (BST *);




