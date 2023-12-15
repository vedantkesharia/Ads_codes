#include <stdio.h>

#include <stdlib.h>

#define SIZE 10
int pot = 0, amcost = 0, cost = 0;
int top = -1, inp_array[SIZE];
void push();
void pop();
void show();

int main()
{
    int choice = 0;
    printf("Potential Method");
    while (choice != 4)
    {
        printf("\nPerform operations on the stack:");
        printf("\n1.Push the element\n2.Pop the element\n3.Show\n4.End");
        printf("\n\nEnter the choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            push();
            break;
        case 2:
            pop();
            break;
        case 3:
            show();
            break;
        case 4:
            break;

        default:
            printf("\nInvalid choice!!");
        }

    }
        printf("\nPotential: %d", pot);
        printf("\nAmortized cost: %d", amcost);
        printf("\nActual Cost: %d", cost);
    return 0;
}

void push()
{
    int x;

    if (top == SIZE - 1)
    {
        printf("\nOverflow!!");
    }
    else
    {
        printf("\nEnter the element to be added onto the stack: ");
        scanf("%d", &x);
        top = top + 1;
        pot += 1;
        amcost += 2;
        cost += 1;
        inp_array[top] = x;
    }
}

void pop()
{
    if (top == -1)
    {
        printf("\nUnderflow!!");
    }
    else
    {
        int n;
        printf("Enter the number of elements to be poped: ");
        scanf("%d", &n);
        printf("Popped elements: ");
        for (int i = 1 && top != -1; i <= n; i++)
        {
            printf("\n%d", inp_array[top]);
            top = top - 1;
            pot -= 1;
            cost += 1;
        }
    }
}

void show()
{
    if (top == -1)
    {
        printf("\nUnderflow!!");
    }
    else
    {
        printf("\nElements present in the stack: \n");
        for (int i = top; i >= 0; --i)
            printf("%d\n", inp_array[i]);
    }
}
