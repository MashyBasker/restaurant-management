#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct node {
    char prod_name[50] , prod_type;
    int prod_price , prod_quant_sold;
    struct node *next;
} node;

node *head=NULL , *budget_head=NULL;
int size=0 , bug_size=0;

void create_menu_list() {
    int no_items , item_price , items_sold;
    char item_name[50] , item_type;
    printf("HOW MANY ITEMS ARE PRESENT IN THE MENU: ");
    scanf("%d" , &no_items);
    for (int i = 0 ; i < no_items ; i++) {
        printf("ENTER THE NAME OF THE ITEM %d: " , i + 1);
        scanf("%s" , &item_name);
        printf("ENTER THE PRICE OF THE ITEM %d: " , i + 1);
        scanf("%d" , &item_price);
        printf("ENTER THE TYPE OF THE ITEM %d [V/N]: " , i + 1);
        scanf(" %c" , &item_type);
        printf("ENTER THE NO. OF ITEM %d SOLD IN PAST WEEK: " , i + 1);
        scanf("%d" , &items_sold);
        push_back(item_name , item_price , items_sold , item_type);
    }
}
void push_back(char name[50] , int price , int quant , char type) {
    if (size >= MAX) {
        printf("STACK OVERFLOW.\n");
        exit(0);
    }
    node *new_node = (node *)malloc(sizeof(node));
    strcpy(new_node->prod_name , name);
    new_node->prod_quant_sold = quant;
    new_node->prod_price = price;
    new_node->prod_type = type;
    new_node->next = head;
    head = new_node;
    size++;
}

void push_budget(char name[50] , int price , int quant , char type) {
    if (bug_size >= MAX) {
        printf("STACK OVERFLOW.\n");
        exit(0);
    }
    node *new_node = (node *)malloc(sizeof(node));
    strcpy(new_node->prod_name , name);
    new_node->prod_quant_sold = quant;
    new_node->prod_price = price;
    new_node->prod_type = type;
    new_node->next = budget_head;
    budget_head = new_node;
    bug_size++;
}

void budget_list(int budget_amt) {
    node *temp=head;
    while (temp != NULL) {
        if (temp->prod_price <= budget_amt) {
            push_budget(temp->prod_name , temp->prod_price , temp->prod_quant_sold , temp->prod_type);
        }
        temp = temp->next;
    }
}

int main() {
    int budget_amount;
    create_menu_list();
    printf("ENTER YOUR BUDGET AMOUNT: ");
    scanf("%d" , &budget_amount);
    budget_list(budget_amount);
    node *ptr=budget_head;
    int i = 1;
    while (ptr != NULL) {
        printf("%d\t\t%s\t\t%d\t\t%d\t\t%c\n" , i , ptr->prod_name , ptr->prod_price , ptr->prod_quant_sold , ptr->prod_type);
        ptr = ptr->next;
    }
    return 0;
}

