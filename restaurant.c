#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct node {
    int s_no;
    char name[50];
    int price;
    int quant_sold;
    struct node *next;
} node;

node *head = NULL;
int size = 0;

// void add_item(char *name , char type , int price , int quantity_sold) {

//     if (size >= MAX) {
//         fprintf(stderr , "STACK OVERFLOW!\n");
//         exit(0);
//     }

//     node *new_item = (node *)malloc(sizeof(node));
//     strncpy(name , new_item->name , sizeof(name));
//     //new_item->type = type;
//     new_item->price = price;
//     new_item->quant_sold = quantity_sold;
//     new_item->next = HEAD;
//     HEAD = new_item;

//     size++; 
//     printf("NEW ITEM ADDED TO MENU!\n");
// }

int skip_line(FILE *fp)
{
    int c;

    while (c = fgetc(fp), c != '\n' && c != EOF)
        ;

    return c;
}

void display_menu() {
    node *temp;
    if (head == NULL) {
        printf("MENU IS EMPTY.\n");
        return;
    } 
    temp = head;
    printf("S.NO\t\tNAME\t\tPRICE\t\tQUANTITY\n\n");
    while (temp != NULL) {
        printf("%d\t\t%s\t\t%d\t\t%d\n" , temp->s_no , temp->name , temp->price , temp->quant_sold);
        temp = temp->next;
    }
}

int main()
{
    node *newNode , *temp;

    FILE *the_file = fopen("excelinput.csv", "r");
    if (the_file == NULL)
    {
        perror("Unable to open file.");
        exit(1);
    }
    char line[200];
    skip_line(the_file);
    int i = 1;
    head = (node *)malloc(sizeof(node));
    int first_line = 0;
    while (fgets(line , sizeof(line) , the_file)) {
        char *val;
        val = strtok(line , ",");
        if (first_line == 4) {
            break;
        }
        else if (first_line == 0) {
            head->s_no = atoi(val);
            first_line++;
        }
        else if (first_line == 1) {
            strncpy (val , head->name , sizeof(val));
            first_line++;
        }
        else if (first_line == 2) {
            head->price = atoi(val);
            first_line++;
        }
        else if (first_line == 3) {
            head->quant_sold = atoi(val);
        }
    }
    head->next = NULL;
    temp = head;
    skip_line(the_file);
    skip_line(the_file);

    while (fgets(line, sizeof(line), the_file))
    {

        char *token;

        token = strtok(line, ",");
        // printf("%s", token);

        while (token != NULL)
        {

            //printf("%-12s", token);
            // The first call to strtok must pass the C string to tokenize, and subsequent calls must specify NULL as the first argument, which tells the function to continue tokenizing the string you passed in first.
            token = strtok(NULL, ",");
            newNode = (node *)malloc(sizeof(node));
            if (i == 1) {
                newNode->s_no = atoi(token);
                i++;
            }
            else if (i == 2) {
                strncpy(token , newNode->name , sizeof(token));
                i++;
            }
            else if (i == 3) {
                newNode->price = atoi(token);
                i++;
            }
            else if (i == 4) {
                newNode->quant_sold = atoi(token);
                i++;
            }
        }
        newNode->next = NULL;
        temp->next = newNode;
        temp = temp->next;
        i = 1;
        //printf("\n");
    }

    display_menu();
    return 0;
}
