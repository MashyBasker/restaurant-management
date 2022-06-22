#include "sack.h"
#include <string.h>
#include "test.h"

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
    if (type == "V")
    {
        new_node->next = veg_head;
        veg_head = new_node;
    }
    else
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

int ll_length(struct node *temp_head) {
    int n = 0;
    struct node *p = temp_head;
    while (p != NULL) {
        n++;
        p = p->next;
    }
    return n;
}
void push_nveg(int s_no , char name[50], int price, int quant, char type)
{
    if (nveg_siz >= MAX)
    {
        printf("STACK OVERFLOW.\n");
        exit(0);
    }
    nveg_siz++;
}*/
void create_list()
{
    struct node *temp = budget_head;
    while (temp != NULL)
    {
        if (temp->preference == 'V')
        {
            push_veg(temp->srNo, temp->proName, temp->price, temp->quan, temp->preference);
        }
        else if (temp->preference == 'N')
        {
            push_nveg(temp->srNo, temp->proName, temp->price, temp->quan, temp->preference);
        }
        temp = temp->next;
    }
}
/*
void create_veg_list()
{
    struct node *temp = budget_head;
    while (temp != NULL)
    {
        if (temp->preference == 'V')
        {
            push_veg(temp->srNo, temp->proName, temp->price, temp->quan, temp->preference);
        }
        else
            temp = temp->next;
    }
}

void create_nveg_list()
{
    struct node *temp = budget_head;
    while (temp != NULL)
    {
        if (temp->preference == 'N')
        {
            push_nveg(temp->srNo, temp->proName, temp->price, temp->quan, temp->preference);
        }
        temp = temp->next;
    }
}
*/
void generate_bill(struct node *temp_head)
{
    int order_no;
    printf("HOW MANY ITEMS DO YOU WANT TO ORDER?: ");
    scanf("%d", &order_no);
    printf("ENTER THE SERIAL NOS. OF THE ITEMS:\n ");
    int order_list[order_no];
    for (int i = 0; i < order_no; i++)
    {
        printf("SERIAL NO. OF ORDER %d: ", i + 1);
        scanf("%d", &order_list[i]);
    }
    int sum = 0;
    struct node *p = temp_head;
    printf("YOUR BILL\n");
    for (int i = 0; i < order_no; i++)
    {
        int serial_no = order_list[i];
        while (p != NULL)
        {
            if (p->srNo == serial_no)
            {
                printf("ORDER %d: %s\n", i + 1, p->proName);
                sum += p->price;
            }
            p = p->next;
        }
        p = temp_head;
    }
    printf("TOTAL: %d\n", sum);
}

int *get_price(struct node *tmp_head) {
    struct node *pte = tmp_head;
    int price_len = ll_length(pte);
    int price_arr[price_len];
    for (int i = 0 ; i < price_len ; i++) {
        price_arr[i] = pte->price;
        pte = pte->next;
    }
    return price_arr;
}

int *get_profit(struct node *tmp_head) {
    struct node *ptr = tmp_head;
    int profit_len = ll_length(ptr);
    int profit_arr[profit_len];
    for (int i = 0 ; i < profit_len ; i++) {
        //profit_arr[i] = ptr->profits;
    }
    return profit_arr;
}

void apply_knapsack() {

}

int main()
{
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

    // create_menu_list();
    printf("ENTER YOUR BUDGET AMOUNT: ");
    scanf("%d", &budget_amount);
    budget_list(budget_amount);
    struct node *ptr = budget_head;
    while (ptr != NULL)
    {
        printf("%d\t\t%s\t\t%d\t\t%d\t\t%c\n", ptr->srNo, ptr->proName, ptr->price, ptr->quan, ptr->preference);
        ptr = ptr->next;
    }
    // SPLIT BETWEEN VEG AND NON VEG
    // create_menu_list();
    char choice;
    printf("DO YOU WANT VEG OR NON-VEG FOOD?[V/N]: ");
    scanf(" %c", &choice);
    if (choice == 'V')
    {
        // create_veg_list();
        create_list();
        struct node *ptr1 = veg_head;
        printf("S.NO\t\tNAME\t\tPRICE\t\tQUANTITY SOLD\t\tMENU TYPE\n");
        printf("+--------------------------------------------------------------------------------+\n\n");
        while (ptr1 != NULL)
        {
            printf("%d\t\t%s\t\t%d\t\t%d\t\t%c\n", ptr1->srNo, ptr1->proName, ptr1->price, ptr1->quan, ptr1->preference);
            ptr1 = ptr1->next;
        }
        generate_bill(veg_head);
    }
    else if (choice == 'N')
    {
        // create_nveg_list();
        create_list();
        struct node *q = nveg_head;
        printf("S.NO\t\tNAME\t\tPRICE\t\tQUANTITY SOLD\t\tMENU TYPE\n");
        printf("+--------------------------------------------------\n\n");
        while (q != NULL)
        {
            printf("%d\t\t%s\t\t%d\t\t%d\t\t%c\n", q->srNo, q->proName, q->price, q->quan, q->preference);
            q = q->next;
        }
        generate_bill(nveg_head);
    }

    return 0;
}
