//Aggregate -> cost, counter, size

#include <stdio.h>
#include <math.h>
int cost = 0;
int incrementCounter(int counter[], int size)
{
    int carry = 1;
    for (int i = 0; i < size && carry; i++)
    {
        int sum = counter[i] + carry;
        counter[i] = sum % 2;
        carry = sum / 2;
        cost++;
    }
    for (int i = size - 1; i >= 0; i--)
    {
        printf("%d", counter[i]);
    }
    printf("\tCost: %d\n", cost);
}
int main()
{
    int size = 4;
    int counter[size];
    for (int i = 0; i < size; i++)
    {
        counter[i] = 0;
    }
    for (int i = 0; i < (pow(2, size) - 1); i++)
    {
        incrementCounter(counter, size);
    }
    return 0;
}