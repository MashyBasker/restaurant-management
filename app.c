#include "sack.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>
//#include "test.h"

#define MAX 100

struct node *head, *veg_head, *nveg_head;
int veg_siz = 0, nveg_siz = 0;

void pushing(int s_no, char name[50], int price, int quant, char type)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->quan = quant;
    new_node->srNo = s_no;
    strcpy(new_node->proName, name);
    new_node->price = price;
    new_node->preference = type;
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

int ll_length(struct node *temp_head) {
    int n = 0;
    struct node *p = temp_head;
    while (p != NULL) {
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
            pushing(temp->srNo, temp->proName, temp->price, temp->quan, temp->preference);
        }
        else if (temp->preference == 'N')
        {
            pushing(temp->srNo, temp->proName, temp->price, temp->quan, temp->preference);
        }
        temp = temp->next;
    }
}
/*
int *get_price_arr(struct node *tmp_head) {
    struct node *pte = tmp_head;
    // int price_len = ll_length(pte);
    int *price_arr = malloc(sizeof(int) * price_len);
    for (int i = 0 ; i < price_len ; i++) {
        price_arr[i] = pte->price;
        pte = pte->next;
    }
    return price_arr;
}

int *get_profit_arr(struct node *tmp_head) {
    struct node *ptr = tmp_head;
    // int profit_len = ll_length(ptr);
    int *profit_arr = malloc(sizeof(int) * profit_len);
    for (int i = 0 ; i < profit_len ; i++) {
        printf("%d\n",profit_arr[i]);
                profit_arr[i] = ptr->profit;
    }
    return profit_arr;
}

int apply_knapsack(struct node *temp_head , int W) {
    struct node *p = temp_head;
    int *profit = get_profit_arr(p);
    int *price = get_price_arr(p);
    // int n = ll_length(p);
    int i, w;
    int K[n + 1][W + 1];

    // /* Build table K[][] in bottom up manner 
    for (i = 0 ; i <= n ; i++)
    {
        for (w = 0; w <= W; w++)
        {
            if (i == 0 || w == 0)
                K[i][w] = 0;
            else if (price[i - 1] <= w)
                K[i][w] = fmax(profit[i - 1] + K[i - 1][w - price[i - 1]], K[i - 1][w]);
            else
                K[i][w] = K[i - 1][w];
        }
    }
    return K[n][W];
}
*/
int* convArrayPrice(struct node *temp_head){
    struct node* temp =temp_head;
    int len=ll_length(temp);
    int arr[len];
    int i = 0;
    while(temp!=NULL){
        arr[i]=temp->price;
        i++;
        temp = temp->next;
    }
    return arr;
    // for (int j=0;j<len;j++)
    // printf("%d\n",arr[j]);

}
/*
int* convArrayProfit(struct node *temp_head){
    struct node* temp =temp_head;
    int len=ll_length(temp);
    int arr[len];
    int i = 0;
    while(temp!=NULL){
        arr[i]=temp->profit;
        i++;
        temp = temp->next;
    }
    return arr;
    // for (int j=0;j<len;j++)
    // printf("%d\n",arr[j]);

}
*/
int main()
{   
    int *priceArr;
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
    printf("What is your budget: ");
    scanf("%d",&budget_amount);

    if (choice == 'V')
    {
        // create_veg_list();
        create_list();
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
        printf("%s\n",veg_head->proName);
        priceArr=convArrayPrice(veg_head);
        // profitArr=convArrayProfit(veg_head);

        // printf("%d" , apply_knapsack(veg_head , budget_amount));
    }
    else if (choice == 'N')
    {
        // create_nveg_list();
        create_list();
        struct node *q = nveg_head;
        printf("S.NO\t\tNAME\t\tPRICE\t\tQUANTITY SOLD\t\tMENU TYPE\n");
        printf("+-------------------------------------------------------------------------------+\n\n");
        while (q != NULL)
        {
            printf("%d\t\t%s\t\t%d\t\t%d\t\t%c\n", q->srNo, q->proName, q->price, q->quan, q->preference);
            q = q->next;
        }
        // generate_bill(nveg_head);
        // printf("%d" , apply_knapsack(nveg_head , budget_amount));
    }
     // create_menu_list();
     /*
    printf("ENTER YOUR BUDGET AMOUNT: ");
    scanf("%d", &budget_amount);
    // budget_list(budget_amount);
    struct node *ptr = budget_head;
    while (ptr != NULL)
    {
        printf("%d\t\t%s\t\t%d\t\t%d\t\t%c\n", ptr->srNo, ptr->proName, ptr->price, ptr->quan, ptr->preference);
        ptr = ptr->next;
    }
    */
    return 0;
}
