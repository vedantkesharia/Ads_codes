#include <stdio.h>
#include <stdlib.h>
struct row
{
    int no, size, cost, amcostAcc, amcostPot, balance, potential;
};
void main()
{
    printf("Enter number of elements: ");
    int n;
    scanf("%d", &n);
    struct row item[n];
    item[0].size = 0;
    item[0].cost = 0;
    item[0].amcostAcc = 0;
    item[0].amcostPot = 0;
    item[0].balance = 0;
    item[0].potential = 0;
    for (int i = 1; i <= n; i++)
    {
        item[i].no = i;
        item[i].amcostAcc = 3;
        if (i > item[i - 1].size)
        {
            if (i == 1)
                item[i].size = 1;
            else
                item[i].size = 2 * item[i - 1].size;
            item[i].cost = item[i - 1].size + 1;
        }
        else
        {
            item[i].size = item[i - 1].size;
            item[i].cost = 1;
        }
        item[i].balance = item[i].amcostAcc - item[i].cost + item[i - 1].balance;
        item[i].potential = 2 * i - item[i].size;
        item[i].amcostPot = item[i].cost + (item[i].potential - item[i - 1].potential);
    }
    while (1)
    {
        printf("Enter choice:\n1.Aggregate\n2.Accounting\n3.Potential\n4.Exit\n");
        int choice, totalcost = 0;
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Item no\tSize\tCost\n");
            for (int i = 1; i <= n; i++)
            {
                printf("%d\t%d\t%d\n", item[i].no, item[i].size, item[i].cost);
                totalcost += item[i].cost;
            }
            int amc = totalcost / n;
            printf("Total cost = %d\nAmortized cost = %d\n", totalcost, amc);
            break;
        case 2:
            printf("Item no\tSize\tCost\tAmcost\tBalance\n");
            for (int i = 1; i <= n; i++)
            {
                printf("%d\t%d\t%d\t%d\t%d\n", item[i].no, item[i].size, item[i].cost, item[i].amcostAcc, item[i].balance);
            }
            break;
        case 3:
            printf("Item no\tSize\tCost\tPotential\tAmortized cost\n");
            for (int i = 1; i <= n; i++)
            {
                printf("%d\t%d\t%d\t%d\t\t%d\n", item[i].no, item[i].size, item[i].cost, item[i].potential, item[i].amcostPot);
            }
            break;
        case 4:
            exit(0);
        default:
            printf("Invalid choice.");
            break;
        }
    }
}