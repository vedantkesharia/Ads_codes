#include <stdio.h>
#include <stdlib.h>
enum Color
{
    RED,
    BLACK
};
struct Node
{
    int data;
    enum Color color;
    struct Node *left, *right, *parent;
};
typedef struct Node Node;
Node *createNode(int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->color = RED;
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}
// Helper function to perform left rotation
void leftRotate(Node **root, Node *x)
{
    Node *y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}
// Helper function to perform right rotation
void rightRotate(Node **root, Node *y)
{
    Node *x = y->left;
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == NULL)
        *root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    x->right = y;
    y->parent = x;
}
// Helper function to fix the Red-Black Tree violations after insertion
void fixInsertion(Node **root, Node *z)
{
    while (z != *root && z->parent->color == RED)
    {
        if (z->parent == z->parent->parent->left)
        {
            Node *y = z->parent->parent->right;
            if (y != NULL && y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->right)
                {
                    z = z->parent;
                    leftRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(root, z->parent->parent);
            }
        }
        else
        {
            Node *y = z->parent->parent->left;
            if (y != NULL && y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->left)
                {
                    z = z->parent;
                    rightRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(root, z->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;
}
// Function to insert a node into the Red-Black Tree
void insert(Node **root, int data)
{
    Node *z = createNode(data);
    Node *y = NULL;
    Node *x = *root;
    while (x != NULL)
    {
        y = x;
        if (z->data < x->data)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (y == NULL)
        *root = z;
    else if (z->data < y->data)
        y->left = z;
    else
        y->right = z;
    fixInsertion(root, z);
}
// Function to print the Red-Black Tree using in-order traversal
void printTree(Node *root)
{
    if (root == NULL)
        return;
    printTree(root->left);
    printf("%d(%s) ", root->data, (root->color == RED) ? "RED" : "BLACK");
    printTree(root->right);
}
int main()
{
    Node *root = NULL;
    int choice;
    int data;
    do
    {
        printf("Red-Black Tree Operations:\n");
        printf("1. Insert\n");
        printf("2. Print\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter data to insert: ");
            scanf("%d", &data);
            insert(&root, data);
            break;
        case 2:
            printf("Red-Black Tree: ");
            printTree(root);
            printf("\n");
            break;
        case 3:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);
    return 0;
}