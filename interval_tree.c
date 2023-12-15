#include <stdio.h>
#include <stdlib.h>
struct Interval
{
    int low, high;
};
struct Node
{
    struct Interval range;
    struct Node *left;
    struct Node *right;
    int max;
};
struct Node *insert(struct Node *root, struct Interval x)
{
    //denoting root's range by range 
    if (root == NULL)
    {
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->range = x; //newnode's range = x
        newNode->max = x.high;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    if (x.low < root->range.low)
    {
    root->left = insert(root->left, x);
    }
    else
    {
    root->right = insert(root->right, x);
    }
    if (root->max < x.high)
    {
        root->max = x.high;
    }
    return root;
}
void inOrder(struct Node *root)
{
    if (root == NULL)
    {
        return;
    }
    inOrder(root->left);
    printf("[%d, %d] max = %d\n", root->range.low, root->range.high, root->max);
    inOrder(root->right);
}
struct Interval isOverlapping(struct Node *root, struct Interval x)
{
    struct Interval dummy = {-1, -1};
    if (root == NULL)
    {
        return dummy;
    }
    if ((x.low > root->range.low && x.low < root->range.high) || (x.high > root->range.low && x.high < root->range.high)) //either low of search node ie x should lie between low and high of root or high of x should lie between low and high of root
    {
        return root->range;
    }
    else if (root->left != NULL && root->left->max > x.low)
    {
        return isOverlapping(root->left, x);
    }
    else
    {
        return isOverlapping(root->right, x);
    }
}

int main()
{
    struct Node *root = NULL;
    root = insert(root, (struct Interval){15, 20});
    root = insert(root, (struct Interval){10, 30});
    root = insert(root, (struct Interval){17, 19});
    root = insert(root, (struct Interval){5, 20});
    root = insert(root, (struct Interval){12, 15});
    root = insert(root, (struct Interval){30, 40});
    printf("Inorder traversal of constructed Interval Tree is\n");
    inOrder(root);
    printf("\n");
    struct Interval i = {6, 7};
    printf("Searching for interval [%d, %d]\n", i.low, i.high);
    struct Interval result = isOverlapping(root, i);
    printf("Overlaps with [%d, %d]\n", result.low, result.high);
    return 0;
}