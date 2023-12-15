#include <stdio.h>
#include <stdlib.h>

// Node Declaration
struct node
{
    int n;
    int degree;
    struct node *parent;
    struct node *child;
    struct node *sibling;
};

// Binomial Heap Structure
struct BinomialHeap
{
    struct node *H;
    struct node *Hr;
    int count;
};

// Function Declarations
struct node *Initializeheap();
int Binomial_link(struct node *, struct node *);
struct node *Create_node(int);
struct node *Union(struct node *, struct node *);
struct node *Insert(struct node *, struct node *);
struct node *Merge(struct node *, struct node *);
int Display(struct node *);
struct node *Search(struct node *, int);

// Initialize Heap
struct node *Initializeheap()
{
    struct node *np;
    np = NULL;
    return np;
}

// Linking nodes in Binomial Heap
int Binomial_link(struct node *y, struct node *z)
{
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree = z->degree + 1;
    return 0;
}

// Create Nodes in Binomial Heap
struct node *Create_node(int k)
{
    struct node *p = (struct node *)malloc(sizeof(struct node));
    if (p == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    p->n = k;
    return p;
}

// Insert Nodes in Binomial Heap
struct node *Insert(struct node *H, struct node *x)
{
    struct node *H1 = Initializeheap();
    x->parent = NULL;
    x->child = NULL;
    x->sibling = NULL;
    x->degree = 0;
    H1 = x;
    H = Union(H, H1);
    return H;
}

// Union Nodes in Binomial Heap
struct node *Union(struct node *H1, struct node *H2)
{
    struct node *H = Initializeheap();
    H = Merge(H1, H2);
    if (H == NULL)
        return H;
    struct node *prev_x;
    struct node *next_x;
    struct node *x;

    prev_x = NULL;
    x = H;
    next_x = x->sibling;
    while (next_x != NULL)
    {
        if ((x->degree != next_x->degree) || ((next_x->sibling != NULL) && (next_x->sibling)->degree == x->degree))
        {
            prev_x = x;
            x = next_x;
        }
        else
        {
            if (x->n <= next_x->n)
            {
                x->sibling = next_x->sibling;
                Binomial_link(next_x, x);
            }
            else
            {
                if (prev_x == NULL)
                    H = next_x;
                else
                    prev_x->sibling = next_x;
                Binomial_link(x, next_x);
                x = next_x;
            }
        }
        next_x = x->sibling;
    }
    return H;
}

// Merge Nodes in Binomial Heap
struct node *Merge(struct node *H1, struct node *H2)
{
    struct node *H = Initializeheap();
    struct node *y;
    struct node *z;
    struct node *a;
    struct node *b;
    y = H1;
    z = H2;
    if (y != NULL)
    {
        if (z != NULL)
        {
            if (y->degree <= z->degree)
                H = y;
            else if (y->degree > z->degree)
                H = z;
        }
        else
            H = y;
    }
    else
        H = z;
    while (y != NULL && z != NULL)
    {
        if (y->degree < z->degree)
        {
            y = y->sibling;
        }
        else if (y->degree == z->degree)
        {
            a = y->sibling;
            y->sibling = z;
            y = a;
        }
        else
        {
            b = z->sibling;
            z->sibling = y;
            z = b;
        }
    }
    return H;
}

// Display Nodes in Binomial Heap
int Display(struct node *H)
{
    if (H == NULL)
    {
        printf("The Heap is empty\n");
        return 0;
    }
    printf("The root nodes are: \n");
    struct node *p;
    p = H;
    while (p != NULL)
    {
        printf("%d", p->n);
        if (p->sibling != NULL)
            printf("-->");
        p = p->sibling;
    }
    printf("\n");
    return 0;
}

int main()
{
    int n, m, l, i;
    struct BinomialHeap bh;
    struct node *p;

    struct node *H;
    H = Initializeheap();
    char ch;
    while (1)
    {
        printf("----------------------------\n");
        printf(" BINOMIAL HEAP\n");
        printf("----------------------------\n");
        printf("1. Insert Element in the heap\n");
        printf("2. Display Heap\n");
        printf("3. Exit\n");
        printf("Enter Your Choice: ");
        scanf("%d", &l);
        switch (l)
        {
        case 1:
            printf("Enter the element to be inserted: ");
            scanf("%d", &m);
            p = Create_node(m);
            H = Insert(H, p);
            break;
        case 2:
            printf("The Heap is: \n");
            Display(H);
            break;
        case 3:
            exit(1);
        default:
            printf("Wrong Choice\n");
        }
    }
    return 0;
}













// #include <stdio.h>
// #include <stdlib.h>

// // Structure representing a node in a binomial heap
// struct BinomialTreeNode {
//     int key;
//     int degree;
//     struct BinomialTreeNode* parent;
//     struct BinomialTreeNode* child;
//     struct BinomialTreeNode* sibling;
// };

// // Structure representing a binomial heap
// struct BinomialHeap {
//     struct BinomialTreeNode* head;
// };

// // Function to create a new binomial tree node
// struct BinomialTreeNode* createNode(int key) {
//     struct BinomialTreeNode* newNode = (struct BinomialTreeNode*)malloc(sizeof(struct BinomialTreeNode));
//     newNode->key = key;
//     newNode->degree = 0;
//     newNode->parent = NULL;
//     newNode->child = NULL;
//     newNode->sibling = NULL;
//     return newNode;
// }

// // Function to link two binomial trees of the same degree
// void link(struct BinomialTreeNode* root1, struct BinomialTreeNode* root2) {
//     root1->parent = root2;
//     root1->sibling = root2->child;
//     root2->child = root1;
//     root2->degree++;
// }

// // Function to merge two binomial heaps
// struct BinomialTreeNode* mergeHeaps(struct BinomialTreeNode* heap1, struct BinomialTreeNode* heap2) {
//     struct BinomialTreeNode* mergedHeap = NULL;
//     struct BinomialTreeNode* prevNode = NULL;
//     struct BinomialTreeNode* currentNode = NULL;

//     while (heap1 != NULL || heap2 != NULL) {
//         if (heap1 == NULL) {
//             currentNode = heap2;
//             heap2 = heap2->sibling;
//         } else if (heap2 == NULL) {
//             currentNode = heap1;
//             heap1 = heap1->sibling;
//         } else {
//             if (heap1->degree <= heap2->degree) {
//                 currentNode = heap1;
//                 heap1 = heap1->sibling;
//             } else {
//                 currentNode = heap2;
//                 heap2 = heap2->sibling;
//             }
//         }

//         if (prevNode == NULL) {
//             mergedHeap = currentNode;
//         } else {
//             prevNode->sibling = currentNode;
//         }
//         prevNode = currentNode;
//     }

//     return mergedHeap;
// }

// // Function to merge two binomial heaps and ensure the resulting heap remains a binomial heap
// struct BinomialTreeNode* binomialHeapUnion(struct BinomialTreeNode* heap1, struct BinomialTreeNode* heap2) {
//     struct BinomialTreeNode* mergedHeap = mergeHeaps(heap1, heap2);

//     if (mergedHeap == NULL) {
//         return NULL;
//     }

//     struct BinomialTreeNode* prevNode = NULL;
//     struct BinomialTreeNode* currentNode = mergedHeap;
//     struct BinomialTreeNode* nextNode = mergedHeap->sibling;

//     while (nextNode != NULL) {
//         //if degree not equal move ahead
//         if (currentNode->degree != nextNode->degree || (nextNode->sibling != NULL && nextNode->sibling->degree == currentNode->degree)) {
//             prevNode = currentNode;
//             currentNode = nextNode;
//         }
//         //else degree equal 
//          else {
//             if (currentNode->key <= nextNode->key) {
//                 currentNode->sibling = nextNode->sibling;
//                 link(nextNode, currentNode);
//             } else {
//                 if (prevNode == NULL) {
//                     mergedHeap = nextNode;
//                 } else {
//                     prevNode->sibling = nextNode;
//                 }
//                 link(currentNode, nextNode);
//                 currentNode = nextNode;
//             }
//         }
//         nextNode = currentNode->sibling;
//     }

//     return mergedHeap;
// }

// // Function to print the keys of a binomial heap
// void printHeap(struct BinomialTreeNode* heap) {
//     printf("Binomial Heap: ");
//     while (heap != NULL) {
//         printf("%d ", heap->key);
//         heap = heap->sibling;
//     }
//     printf("\n");
// }

// // Example usage
// int main() {
//     struct BinomialHeap binomialHeap1, binomialHeap2;
//     binomialHeap1.head = NULL;
//     binomialHeap2.head = NULL;

//     // Insert keys into the first binomial heap
//     binomialHeap1.head = createNode(4);
//     binomialHeap1.head->sibling = createNode(7);

//     // Insert keys into the second binomial heap
//     binomialHeap2.head = createNode(2);
//     binomialHeap2.head->sibling = createNode(5);

//     // Print the first binomial heap
//     printf("First ");
//     printHeap(binomialHeap1.head);

//     // Print the second binomial heap
//     printf("Second ");
//     printHeap(binomialHeap2.head);

//     // Merge the two binomial heaps
//     struct BinomialTreeNode* mergedHeap = binomialHeapUnion(binomialHeap1.head, binomialHeap2.head);

//     // Print the merged binomial heap
//     printf("Merged ");
//     printHeap(mergedHeap);

//     return 0;
// }
