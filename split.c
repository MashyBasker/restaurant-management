#include <stdio.h>
#include <stdlib.h>
#include "sack.h"
#include <string.h>

#define MAX 100

struct node *head, *veg_head, *nveg_head;
// int size1 = 0;
int veg_siz = 0, nveg_siz = 0;

void push_veg(char name[50], int price, int quant, char type)
{
    if (veg_siz >= MAX)
    {
        printf("STACK OVERFLOW.\n");
        exit(0);
    }
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->quan = quant;
    strcpy(new_node->proName, name);
    new_node->price = price;
    new_node->preference = type;
    new_node->next = veg_head;
    veg_head = new_node;
    veg_siz++;
}

void push_nveg(char name[50], int price, int quant, char type)
{
    if (nveg_siz >= MAX)
    {
        printf("STACK OVERFLOW.\n");
        exit(0);
    }
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->quan = quant;
    strcpy(new_node->proName, name);
    new_node->price = price;
    new_node->preference = type;
    new_node->next = nveg_head;
    nveg_head = new_node;

    nveg_siz++;
}
/*


*/
void create_veg_list()
{
    struct node *temp = budget_head;
    while (temp != NULL)
    {
        if (temp->preference == 'V')
        {
            push_veg(temp->proName, temp->price, temp->quan, temp->preference);
        }
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
            push_nveg(temp->proName, temp->price, temp->quan, temp->preference);
        }
        temp = temp->next;
    }
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
    int index = 1;
    while (ptr != NULL)
    {
        printf("%d\t\t%s\t\t%d\t\t%d\t\t%c\n", index, ptr->proName, ptr->price, ptr->quan, ptr->preference);
        ptr = ptr->next;
        index++;
    }
    // SPLIT BETWEEN VEG AND NON VEG
    // create_menu_list();
    create_veg_list();
    create_nveg_list();
    printf("########### THE VEG MENU ###########\n\n");
    struct node *ptr1 = veg_head;
    int i = 1;
    while (ptr1 != NULL)
    {
        printf("%d\t\t%s\t\t%d\t\t%d\t\t%c\n", i, ptr1->proName, ptr1->price, ptr1->quan, ptr1->preference);
        i++;
        ptr1 = ptr1->next;
    }
    printf("\n");
    int j = 1;
    struct node *qt = nveg_head;
    printf("######### THE NON-VEG MENU ##########\n\n");
    while (qt != NULL)
    {
        printf("%d\t\t%s\t\t%d\t\t%d\t\t%c\n", j, qt->proName, qt->price, qt->quan, qt->preference);
        j++;
        qt = qt->next;
    }
    return 0;
}
