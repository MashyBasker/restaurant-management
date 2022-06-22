#include "restaurant.h"

#define MAX 100

struct node *budget_head = NULL;
int size = 0, bug_size = 0;

void push_budget(int s_no, char name[50], int price, int quant, char type)
{
    if (bug_size >= MAX)
    {
        printf("STACK OVERFLOW.\n");
        exit(0);
    }
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    strcpy(new_node->proName, name);
    new_node->srNo = s_no;
    new_node->quan = quant;
    new_node->price = price;
    new_node->preference = type;
    new_node->next = budget_head;
    budget_head = new_node;
    bug_size++;
}

void budget_list(int budget_amt)
{
    struct node *temp = head;
    while (temp != NULL)
    {
        if (temp->price <= budget_amt)
        {
            push_budget(temp->srNo, temp->proName, temp->price, temp->quan, temp->preference);
        }
        temp = temp->next;
    }
}
