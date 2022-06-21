#include <stdio.h>
#include "restaurant.h"
#include <stdlib.h>
#include <string.h>

#define MAX 100

/*
typedef struct node
{
    char prod_name[50], prod_type;
    int prod_price, prod_quant_sold;
    struct node *next;
} node;
*/

struct node *budget_head = NULL;
int size = 0, bug_size = 0;

/*
void create_menu_list()
{
    int no_items, item_price, items_sold;
    char item_name[50], item_type;
    printf("HOW MANY ITEMS ARE PRESENT IN THE MENU: ");
    scanf("%d", &no_items);
    for (int i = 0; i < no_items; i++)
    {
        printf("ENTER THE NAME OF THE ITEM %d: ", i + 1);
        scanf("%s", &item_name);
        printf("ENTER THE PRICE OF THE ITEM %d: ", i + 1);
        scanf("%d", &item_price);
        printf("ENTER THE TYPE OF THE ITEM %d [V/N]: ", i + 1);
        scanf(" %c", &item_type);
        printf("ENTER THE NO. OF ITEM %d SOLD IN PAST WEEK: ", i + 1);
        scanf("%d", &items_sold);
        push_back(item_name, item_price, items_sold, item_type);
    }
}
void push_back(char name[50], int price, int quant, char type)
{
    if (size >= MAX)
    {
        printf("STACK OVERFLOW.\n");
        exit(0);
    }
    struct node *new_node = (node *)malloc(sizeof(node));
    strcpy(new_node->prod_name, name);
    new_node->prod_quant_sold = quant;
    new_node->prod_price = price;
    new_node->prod_type = type;
    new_node->next = head;
    head = new_node;
    size++;
}
*/
void push_budget(char name[50], int price, int quant, char type)
{
    if (bug_size >= MAX)
    {
        printf("STACK OVERFLOW.\n");
        exit(0);
    }
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    strcpy(new_node->proName, name);
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
            push_budget(temp->proName, temp->price, temp->quan, temp->preference);
        }
        temp = temp->next;
    }
}
