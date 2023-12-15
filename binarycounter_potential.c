#include <stdio.h>
#include <math.h>

// for{while{if{for{if}}}}
// prev_potential, potential, prevones, currentones, tot

void main()
{
    float tot = 0;
    int arr[4] = {0};
    printf("Enter value between 0 to %0.2f\n", pow(2, 4));
    float n;
    scanf("%f", &n);
    float prev_potential = 0;
    printf("Counter:0, Cost:0\n");
    float prevones = 0;
    for (int j = 0; j < n; j++)
    {
        float currentones = 0;
        float potential = 0;
        int i = 0;
        while (arr[i] == 1 && i < 4)
        {
            arr[i] = 0;
            tot++;
            i++;
        }
        if (i < 4)
        {
            tot++;
            arr[i] = 1;
        }
        for (int k = 0; k < 4; k++)
        {
            if (arr[k] == 1)
            {
                currentones++;
            }
        }
        float current_cost = tot;
        potential = current_cost + potential - prev_potential;
        prev_potential = current_cost;
        float amort = potential + (currentones - prevones);
        prevones = currentones;
        printf("Counter:%d, Potential:%0.2f, Current Cost:%0.2f, amort Cost:%0.2f\n", j + 1, currentones, potential, amort);
    }
    float avg_cost = tot / n;
    printf("\nAvg Cost:%0.2f\n", avg_cost);
}