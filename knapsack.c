#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct node {
    char prod_name[50];
    int prod_price , prod_quant_sold;
    char prod_type;
    struct node *next;
} node;
node *head , *veg_head , *nveg_head;
int size = 0;
int veg_siz=0 , nveg_siz=0;

void push_back(char name[50] , int price , int quant , char type) {
    if (size >= MAX) {
        printf("STACK OVERFLOWn\n");
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

void push_veg(char name[50] , int price , int quant , char type) {
    if (veg_siz >= MAX) {
        printf("STACK OVERFLOW.\n");
        exit(0);
    }
    node *new_node = (node *)malloc(sizeof(node));
    new_node->prod_quant_sold = quant;
    strcpy(new_node->prod_name , name);
    new_node->prod_price = price;
    new_node->prod_type = type;
    new_node->next = veg_head;
    veg_head = new_node;
    veg_siz++;
}

void push_nveg(char name[50] , int price , int quant , char type) {
    if (nveg_siz >= MAX) {
        printf("STACK OVERFLOW.\n");
        exit(0);
    }
    node *new_node = (node *)malloc(sizeof(node));
    new_node->prod_quant_sold = quant;
    strcpy(name , new_node->prod_name);
    new_node->prod_price = price;
    new_node->prod_type = type;
    new_node->next = nveg_head;
    nveg_head = new_node;
    nveg_siz++;
}

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

void create_veg_list() {
    node *temp = head;
    while (temp != NULL) {
        if (temp->prod_type == 'V') {
            push_veg(temp->prod_name , temp->prod_price , temp->prod_quant_sold , temp->prod_type);
        }
        temp = temp->next;
    }
}

void create_nveg_list() {
    node *temp = head;
    while (temp != NULL) {
        if (temp->prod_type == 'N') {
            push_nveg(temp->prod_name , temp->prod_price , temp->prod_quant_sold , temp->prod_type);
        }
        temp = temp->next;
    }
}

int main() {
    create_menu_list();
    create_veg_list();
    create_nveg_list();
    printf("########### THE VEG MENU ###########\n\n");
    node *ptr = veg_head;
    int i = 1;
    while (ptr != NULL) {
        printf("%d\t\t%s\t\t%d\t\t%d\t\t%c\n" , i , ptr->prod_name , ptr->prod_price , ptr->prod_quant_sold , ptr->prod_type);
        i++;
        ptr = ptr->next;
    }
    printf("\n");
    int j = 1;
    node *qt = nveg_head;
    printf("######### THE NON-VEG MENU ##########\n\n");
    while (qt != NULL) {
        printf("%d\t\t%s\t\t%d\t\t%d\t\t%c\n" , j , qt->prod_name , qt->prod_price , qt->prod_quant_sold , qt->prod_type);
        j++;
        qt = qt->next;
    }
    return 0;
}



