#include <stdio.h>
#include <stdlib.h>

struct BinomialTreeNode {
    int key;
    int degree;
    struct BinomialTreeNode* parent;
    struct BinomialTreeNode* child;
    struct BinomialTreeNode* sibling;
};

struct BinomialHeap {
    struct BinomialTreeNode* head;
};

struct BinomialTreeNode* createNode(int key) {
    struct BinomialTreeNode* newNode = (struct BinomialTreeNode*)malloc(sizeof(struct BinomialTreeNode));
    newNode->key = key;
    newNode->degree = 0;
    newNode->parent = NULL;
    newNode->child = NULL;
    newNode->sibling = NULL;
    return newNode;
}

void link(struct BinomialTreeNode* root1, struct BinomialTreeNode* root2) {
    root1->parent = root2;
    root1->sibling = root2->child;
    root2->child = root1;
    root2->degree++;
}

struct BinomialTreeNode* mergeHeaps(struct BinomialTreeNode* heap1, struct BinomialTreeNode* heap2) {
    struct BinomialTreeNode* mergedHeap = NULL;
    struct BinomialTreeNode* prevNode = NULL;
    struct BinomialTreeNode* currentNode = NULL;

    while (heap1 != NULL || heap2 != NULL) {
        if (heap1 == NULL) {
            currentNode = heap2;
            heap2 = heap2->sibling;
        } else if (heap2 == NULL) {
            currentNode = heap1;
            heap1 = heap1->sibling;
        } else {
            if (heap1->degree <= heap2->degree) {
                currentNode = heap1;
                heap1 = heap1->sibling;
            } else {
                currentNode = heap2;
                heap2 = heap2->sibling;
            }
        }

        if (prevNode == NULL) {
            mergedHeap = currentNode;
        } else {
            prevNode->sibling = currentNode;
        }
        prevNode = currentNode;
    }

    return mergedHeap;
}

struct BinomialTreeNode* binomialHeapUnion(struct BinomialTreeNode* heap1, struct BinomialTreeNode* heap2) {
    struct BinomialTreeNode* mergedHeap = mergeHeaps(heap1, heap2);

    if (mergedHeap == NULL) {
        return NULL;
    }

    struct BinomialTreeNode* prevNode = NULL;
    struct BinomialTreeNode* currentNode = mergedHeap;
    struct BinomialTreeNode* nextNode = mergedHeap->sibling;

    while (nextNode != NULL) {
        if (currentNode->degree != nextNode->degree || (nextNode->sibling != NULL && nextNode->sibling->degree == currentNode->degree)) {
            prevNode = currentNode;
            currentNode = nextNode;
        } else {
            //else degree are equal
            if (currentNode->key <= nextNode->key) {
                currentNode->sibling = nextNode->sibling;
                link(nextNode, currentNode);
            } else {
                if (prevNode == NULL) {
                    mergedHeap = nextNode;
                } else {
                    prevNode->sibling = nextNode;
                }
                link(currentNode, nextNode);
                currentNode = nextNode;
            }
        }
        nextNode = currentNode->sibling;
    }

    return mergedHeap;
}

void displayHeap(struct BinomialTreeNode* heap, int level) {
    while (heap != NULL) {
        printf("(%d,%d) ", heap->key, level);
        if (heap->child != NULL) {
            displayHeap(heap->child, level + 1);
        }
        heap = heap->sibling;
    }
}

int main() {
    struct BinomialHeap binomialHeap1, binomialHeap2;
    binomialHeap1.head = createNode(4);
    binomialHeap1.head->child = createNode(7);

    binomialHeap2.head = createNode(3);
    binomialHeap2.head->child = createNode(9);

    printf("First Binomial Heap: ");
    displayHeap(binomialHeap1.head, 0);
    printf("\n");

    printf("Second Binomial Heap: ");
    displayHeap(binomialHeap2.head, 0);
    printf("\n");

    struct BinomialTreeNode* mergedHeap = binomialHeapUnion(binomialHeap1.head, binomialHeap2.head);

    printf("Merged Binomial Heap: ");
    displayHeap(mergedHeap, 0);
    printf("\n");

    return 0;
}
