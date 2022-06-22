/* C program – Dynamic Programming implementation of 0-1 Knapsack problem */
#include <stdio.h>

/* Function to find maximum of two integers */
int max(int a, int b) { return (a > b) ? a : b; }

// Returns the maximum value that can be put in a knapsack of capacity W
int knapSack(int W, int weight[], int value[], int n)
{
    int i, w;
    int K[n + 1][W + 1];

    /* Build table K[][] in bottom up manner */
    for (i = 0; i <= n; i++)
    {
        for (w = 0; w <= W; w++)
        {
            if (i == 0 || w == 0)
                K[i][w] = 0;
            else if (weight[i - 1] <= w)
                K[i][w] = max(value[i - 1] + K[i - 1][w - weight[i - 1]], K[i - 1][w]);
            else
                K[i][w] = K[i - 1][w];
        }
    }

    return K[n][W];
}

int main()
{
    int n;
    printf("\nEnter the number of items : ");
    scanf("%d", &n);
    // n = 10;
    int value[n];
    int weight[n];
    int i;
    printf("\nEnter the items price  and profit \n");
    for (i = 0; i < n; i++)
    {
        scanf("%d %d", &weight[i], &value[i]);
    }
    int W;
    printf("\nEnter the budget of the knapsack : ");
    scanf("%d", &W);
    printf("\nMaximum value in a 0-1 knapsack : %d\n", knapSack(W, weight, value, n));
    return 0;
}