#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// tree[index] -> current node
// buildSegmentTree(arr, tree, 2 * index + 1, left, mid); -> left side of given node
// buildSegmentTree(arr, tree, 2 * index + 2, mid + 1, right); -> right side of given node


void buildSegmentTree(int arr[], int treeMin[], int treeMax[], int treeSum[], int index, int left, int right)
{
    if (left == right)
    {
        treeMin[index] = arr[left];
        treeMax[index] = arr[left];
        treeSum[index] = arr[left];
    }
    else
    {
        int mid = (left + right) / 2;
        buildSegmentTree(arr, treeMin, treeMax, treeSum, 2 * index + 1, left, mid);
        buildSegmentTree(arr, treeMin, treeMax, treeSum, 2 * index + 2, mid + 1, right);
        treeMin[index] = (treeMin[2 * index + 1] < treeMin[2 * index + 2]) ? treeMin[2 * index + 1] : treeMin[2 * index + 2];
        treeMax[index] = (treeMax[2 * index + 1] > treeMax[2 * index + 2]) ? treeMax[2 * index + 1] : treeMax[2 * index + 2];
        treeSum[index] = treeSum[2 * index + 1] + treeSum[2 * index + 2];
    }
}

int rangeMinQuery(int treeMin[], int index, int left, int right, int queryLeft, int queryRight)
{
    if (queryLeft <= left && queryRight >= right)
    {
        return treeMin[index];
    }
    if (queryRight < left || queryLeft > right)
    {
        return INT_MAX; // Return a large value for out-of-range queries
    }
    int mid = (left + right) / 2;
    int leftMin = rangeMinQuery(treeMin, 2 * index + 1, left, mid, queryLeft, queryRight);
    int rightMin = rangeMinQuery(treeMin, 2 * index + 2, mid + 1, right, queryLeft, queryRight);
    return (leftMin < rightMin) ? leftMin : rightMin;
}

int rangeMaxQuery(int treeMax[], int index, int left, int right, int queryLeft, int queryRight)
{
    if (queryLeft <= left && queryRight >= right)
    {
        return treeMax[index];
    }
    if (queryRight < left || queryLeft > right)
    {
        return INT_MIN; // Return a small value for out-of-range queries
    }
    int mid = (left + right) / 2;
    int leftMax = rangeMaxQuery(treeMax, 2 * index + 1, left, mid, queryLeft, queryRight);
    int rightMax = rangeMaxQuery(treeMax, 2 * index + 2, mid + 1, right, queryLeft, queryRight);
    return (leftMax > rightMax) ? leftMax : rightMax;
}

int rangeSumQuery(int treeSum[], int index, int left, int right, int queryLeft, int queryRight)
{
    if (queryLeft <= left && queryRight >= right)
    {
        return treeSum[index];
    }
    if (queryRight < left || queryLeft > right)
    {
        return 0;
    }
    int mid = (left + right) / 2;
    int leftSum = rangeSumQuery(treeSum, 2 * index + 1, left, mid, queryLeft, queryRight);
    int rightSum = rangeSumQuery(treeSum, 2 * index + 2, mid + 1, right, queryLeft, queryRight);
    return leftSum + rightSum;
}

int main()
{
    int n = 8;
    int arr[] = {2, 3, -1, 5, -2, 4, 8, 10};
    int treeSize = 4 * n;
    int treeMin[treeSize];
    int treeMax[treeSize];
    int treeSum[treeSize];

    for (int i = 0; i < treeSize; i++)
    {
        treeMin[i] = INT_MAX;
        treeMax[i] = INT_MIN;
        treeSum[i] = 0;
    }

    buildSegmentTree(arr, treeMin, treeMax, treeSum, 0, 0, n - 1);

    int queryLeft = 2, queryRight = 5;
    int minVal = rangeMinQuery(treeMin, 0, 0, n - 1, queryLeft, queryRight);
    int maxVal = rangeMaxQuery(treeMax, 0, 0, n - 1, queryLeft, queryRight);
    int sumVal = rangeSumQuery(treeSum, 0, 0, n - 1, queryLeft, queryRight);

    printf("Min value in the range [%d, %d] is %d\n", queryLeft, queryRight, minVal);
    printf("Max value in the range [%d, %d] is %d\n", queryLeft, queryRight, maxVal);
    printf("Sum of elements in the range [%d, %d] is %d\n", queryLeft, queryRight, sumVal);

    return 0;
}












// #include <stdio.h>
// #include <stdlib.h>

// // tree[index] -> current node
// // buildSegmentTree(arr, tree, 2 * index + 1, left, mid); -> left side of given node
// // buildSegmentTree(arr, tree, 2 * index + 2, mid + 1, right); -> right side of given node

// void buildSegmentTree(int arr[], int tree[], int index, int left, int right)
// {
//     if (left == right)
//     {
//         tree[index] = arr[left];
//     }
//     else
//     {
//         int mid = (left + right) / 2;
//         buildSegmentTree(arr, tree, 2 * index + 1, left, mid);
//         buildSegmentTree(arr, tree, 2 * index + 2, mid + 1, right);
//         tree[index] = tree[2 * index + 1] + tree[2 * index + 2]; //index val = val of left side + val of right side
//     }
// }
// int rangeSumQuery(int tree[], int index, int left, int right, int queryLeft, int queryRight)
// {
//     if (queryLeft <= left && queryRight >= right)
//     {
//         return tree[index];
//     }
//     if (queryRight < left || queryLeft > right)
//     {
//         return 0;
//     }
//     int mid = (left + right) / 2;
//     int leftSum = rangeSumQuery(tree, 2 * index + 1, left, mid, queryLeft, queryRight);
//     int rightSum = rangeSumQuery(tree, 2 * index + 2, mid + 1, right, queryLeft, queryRight);
//     return leftSum + rightSum;
// }
// void updateElement(int arr[], int tree[], int index, int left, int right, int updateIndex, int newValue)
// {
//     if (left == right)
//     {
//         arr[updateIndex] = newValue;
//         tree[index] = newValue;
//     }
//     else
//     {
//         int mid = (left + right) / 2;
//         if (updateIndex <= mid)
//         {
//             updateElement(arr, tree, 2 * index + 1, left, mid, updateIndex, newValue);
//         }
//         else
//         {
//             updateElement(arr, tree, 2 * index + 2, mid + 1, right, updateIndex, newValue);
//         }
//         tree[index] = tree[2 * index + 1] + tree[2 * index + 2];
//     }
// }
// int main()
// {
//     int n = 8;
//     int arr[] = {2, 3, -1, 5, -2, 4, 8, 10};
//     int treeSize = 4 * n;
//     int tree[treeSize];
//     for (int i = 0; i < treeSize; i++)
//     {
//         tree[i] = 0;
//     }
//     buildSegmentTree(arr, tree, 0, 0, n - 1);
//     int queryLeft = 3, queryRight = 6;
//     int sum = rangeSumQuery(tree, 0, 0, n - 1, queryLeft, queryRight);
//     printf("Sum of elements in the range [%d, %d] is %d\n", queryLeft, queryRight, sum);
//     int updateIndex = 2, newValue = 10;
//     updateElement(arr, tree, 0, 0, n - 1, updateIndex, newValue);
//     queryLeft = 2;
//     queryRight = 5;
//     sum = rangeSumQuery(tree, 0, 0, n - 1, queryLeft, queryRight);
//     printf("Updated sum of elements in the range [%d, %d] is %d\n", queryLeft, queryRight, sum);
//     return 0;
// }