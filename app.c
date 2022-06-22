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
    // printf("%d\n", res);

    w = budget;
    printf("\n\nORDER THIS FOR BEST TASTE\n\n");
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
            // printf("PRODUCT PRICE:%d\n ", price[i - 1]);
            while (tempro != NULL)
            {
                if (price[i - 1] == tempro->price)
                {
                    printf("Serial no:%d\t Product Name:%s\t Price:%d\t Prefernce:%c\t  \n", tempro->srNo, tempro->proName, tempro->price, tempro->preference);
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
void greetings() // Exit Screen
{

    printf("\n\n\n                  Thank You Very Much          \n ");
    printf("             +============================+          \n\n");
    printf("               && Please come again && \n\n");
}

int main()
{
    struct node *temp;
    int *priceArr, *profitArr;
    int budget_amount;
    char choice;
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
    /// Start
    printf("\n\n\n================ Welcome to Tikka ‘n’ Talk ================\n\n\n");
    int ch;

    printf("Available choices : \n");
    printf("1-->Login as admin\n");
    printf("2-->Login as customer\n");
    printf("3-->Exit from program\n");
    printf("\n");
    printf("Please enter your choice : ");
    scanf("%d", &ch);
    printf("\n");
    switch (ch)
    {
    case 1:
        MergeSort(&head);
        display();
        break;
    case 2:

        printf("DO YOU WANT VEG OR NON-VEG FOOD?[V/N]: ");
        scanf(" %c", &choice);

        if (choice == 'V')
        {
            // create_veg_list();
            create_list();
            temp = veg_head;

            // printf("%s\n", veg_head->proName);
            priceArr = convArrayPrice(veg_head);
            profitArr = convArrayProfit(veg_head);

            // printf("%d" , apply_knapsack(veg_head , budget_amount));
        }
        else if (choice == 'N')
        {

            create_list();
            temp = nveg_head;

            // printf("%s\n", veg_head->proName);
            priceArr = convArrayPrice(nveg_head);
            profitArr = convArrayProfit(nveg_head);
        }

        printf("ENTER YOUR BUDGET AMOUNT: ");
        scanf("%d", &budget_amount);

        knapSack(budget_amount, priceArr, profitArr, 5, temp);

        struct node *ptr = budget_head;
        while (ptr != NULL)
        {
            printf("%d\t\t%s\t\t%d\t\t%d\t\t%c\n", ptr->srNo, ptr->proName, ptr->price, ptr->quan, ptr->preference);
            ptr = ptr->next;
        }
        // vegnonveg();
        break;
    default:
        printf("Enter the correct choice\n");
    }
    greetings();
    // END

    // MergeSort(&head);
    // display();

    // SPLIT BETWEEN VEG AND NON VEG
    // create_menu_list();

    return 0;
}
