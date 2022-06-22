#include "sack.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX 100

struct node *head, *veg_head, *nveg_head;
int veg_siz = 0, nveg_siz = 0;

void pushing(int s_no, char name[50], int price, int quant, char type, int profit)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->quan = quant;
    new_node->srNo = s_no;
    strcpy(new_node->proName, name);
    new_node->price = price;
    new_node->preference = type;
    new_node->profit = profit;
    if (type == 'V')
    {
        new_node->next = veg_head;
        veg_head = new_node;
    }
    else if (type == 'N')
    {
        new_node->next = nveg_head;
        nveg_head = new_node;
    }
}
/*
void push_veg(int s_no, char name[50], int price, int quant, char type)
{
    if (veg_siz >= MAX)
    {
        printf("STACK OVERFLOW.\n");
        exit(0);
    }
    pushing(s_no, name, price, quant, type);

    veg_siz++;
}
*/

int ll_length(struct node *temp_head)
{
    int n = 0;
    struct node *p = temp_head;
    while (p != NULL)
    {
        n++;
        p = p->next;
    }
    return n;
}

void create_list()
{
    // struct node *temp = budget_head;
    struct node *temp = head;
    while (temp != NULL)
    {
        if (temp->preference == 'V')
        {
            pushing(temp->srNo, temp->proName, temp->price, temp->quan, temp->preference, temp->profit);
        }
        else if (temp->preference == 'N')
        {
            pushing(temp->srNo, temp->proName, temp->price, temp->quan, temp->preference, temp->profit);
        }
        temp = temp->next;
    }
}

int *convArrayPrice(struct node *temp_head)
{
    struct node *temp = temp_head;
    int len = ll_length(temp);
    int *arr = malloc(sizeof(int) * len);
    ;
    int i = 0;
    while (temp != NULL)
    {
        arr[i] = temp->price;
        i++;
        temp = temp->next;
    }
    for (int j = 0; j < len; j++)
        printf("%d\n", arr[j]);
    return arr;
}

int *convArrayProfit(struct node *temp_head)
{
    struct node *temp = temp_head;
    int len = ll_length(temp);
    int *arr = malloc(sizeof(int) * len);
    int i = 0;
    while (temp != NULL)
    {
        arr[i] = temp->profit;
        i++;
        temp = temp->next;
    }
    for (int j = 0; j < len; j++)
        printf("%d\n", arr[j]);
    return arr;
}
int max(int a, int b) { return (a > b) ? a : b; }

// Returns the maximum value that can be put in a knapsack of capacity W
void knapSack(int budget, int price[], int profit[], int n, struct node *final)
{
    struct node *tempro = final;
    int i, w;
    int K[n + 1][budget + 1];

    /* Build table K[][] in bottom up manner */
    for (i = 0; i <= n; i++)
    {
        for (w = 0; w <= budget; w++)
        {
            if (i == 0 || w == 0)
                K[i][w] = 0;
            else if (price[i - 1] <= w)
                K[i][w] = max(profit[i - 1] + K[i - 1][w - price[i - 1]], K[i - 1][w]);
            else
                K[i][w] = K[i - 1][w];
        }
    }

    int res = K[n][budget];
    printf("%d\n", res);

    w = budget;
    printf("Order this for best profit \n");
    for (i = n; i > 0 && res > 0; i--)
    {

        // either the result comes from the top
        // (K[i-1][w]) or from (val[i-1] + K[i-1]
        // [w-wt[i-1]]) as in Knapsack table. If
        // it comes from the latter one/ it means
        // the item is included.
        if (res == K[i - 1][w])
            continue;
        else
        {

            // This item is included.
            // This is price
            printf("PRODUCT PRICE:%d\n ", price[i - 1]);
            while (tempro != NULL)
            {
                if (price[i - 1] == tempro->price)
                {
                    printf("Serial no:%d\t Product Name:%s\t Price:%d\t Quantity:%d\t Prefernce:%c\t Profit:%d \n", tempro->srNo, tempro->proName, tempro->price, tempro->quan, tempro->preference, tempro->profit);
                }
                tempro = tempro->next;
            }
            tempro = final;

            // Since this price is included its
            // profit is deducted
            res = res - profit[i - 1];
            w = w - price[i - 1];
        }
    }
}

int main()
{
    struct node *temp;
    int *priceArr, *profitArr;
    int budget_amount;
    FILE *the_file = fopen("excelinput.csv", "r");
    if (the_file == NULL)
    {
        perror("Unable to open file.");
        exit(1);
    }
    char line[200];
    skip_line(the_file);

    while (fgets(line, sizeof(line), the_file))
    {
        push(line);
        // disk(line);
        // printf("\n");
    }

    MergeSort(&head);
    display();

    // SPLIT BETWEEN VEG AND NON VEG
    // create_menu_list();
    char choice;
    printf("DO YOU WANT VEG OR NON-VEG FOOD?[V/N]: ");
    scanf(" %c", &choice);
    // printf("What is your budget: ");
    // scanf("%d", &budget_amount);

    if (choice == 'V')
    {
        // create_veg_list();
        create_list();
        temp = veg_head;
        /*
        struct node *ptr1 = veg_head;
        printf("S.NO\t\tNAME\t\tPRICE\t\tQUANTITY SOLD\t\tMENU TYPE\n");
        printf("+--------------------------------------------------------------------------------+\n\n");
        while (ptr1 != NULL)
        {
            printf("%d\t\t%s\t\t%d\t\t%d\t\t%c\n", ptr1->srNo, ptr1->proName, ptr1->price, ptr1->quan, ptr1->preference);
            ptr1 = ptr1->next;
        }
        */
        // generate_bill(veg_head);
        printf("%s\n", veg_head->proName);
        priceArr = convArrayPrice(veg_head);
        profitArr = convArrayProfit(veg_head);

        // printf("%d" , apply_knapsack(veg_head , budget_amount));
    }
    else if (choice == 'N')
    {
        // create_nveg_list();
        create_list();
        temp = nveg_head;
        /*
        struct node *q = nveg_head;
        printf("S.NO\t\tNAME\t\tPRICE\t\tQUANTITY SOLD\t\tMENU TYPE\n");
        printf("+-------------------------------------------------------------------------------+\n\n");
        while (q != NULL)
        {
            printf("%d\t\t%s\t\t%d\t\t%d\t\t%c\n", q->srNo, q->proName, q->price, q->quan, q->preference);
            q = q->next;
        }
        */
        // generate_bill(nveg_head);
        // printf("%d" , apply_knapsack(nveg_head , budget_amount));
        printf("%s\n", veg_head->proName);
        priceArr = convArrayPrice(nveg_head);
        profitArr = convArrayProfit(nveg_head);
    }
    // create_menu_list();

    printf("ENTER YOUR BUDGET AMOUNT: ");
    scanf("%d", &budget_amount);

    knapSack(budget_amount, priceArr, profitArr, 5, temp);
    // budget_list(budget_amount);

    struct node *ptr = budget_head;
    while (ptr != NULL)
    {
        printf("%d\t\t%s\t\t%d\t\t%d\t\t%c\n", ptr->srNo, ptr->proName, ptr->price, ptr->quan, ptr->preference);
        ptr = ptr->next;
    }

    return 0;
}
