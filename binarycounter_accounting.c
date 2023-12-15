#include <stdio.h>
#include <math.h>
int cost = 0, balance = 0;
int incrementCounter(int counter[], int size)
{
    int carry = 1;
    int oneToZero = 0, zeroToOne = 0, actualCost = 0, amortizedCost = 2;
    for (int i = 0; i < size && carry; i++)
    {
        int sum = counter[i] + carry;
        counter[i] = sum % 2;
        carry = sum / 2;
        if (carry == 1)
        {
            oneToZero++;
        }
        else
        {
            zeroToOne++;
        }
    }
    actualCost = oneToZero + zeroToOne;
    if (amortizedCost > actualCost)
    {
        int diff = amortizedCost - actualCost;
        balance += diff;
    }
    else
    {
        int diff = actualCost - amortizedCost;
        balance -= diff;
    }
    for (int i = size - 1; i >= 0; i--)
    {
        printf("%d", counter[i]);
    }
    printf("\tCredits: %d\n", balance);
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
}