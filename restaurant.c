#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    int srNo, quan, price;
    char proName[50];
    char preference[50];
    struct node *next;
};

struct node *head;

int skip_line(FILE *fp)
{
    int c;

    while (c = fgetc(fp), c != '\n' && c != EOF)
        ;

    return c;
}

void disk(char *line)
{
    printf("%s", line);
}
void push(char *line)
{

    struct node *ptr = (struct node *)malloc(sizeof(struct node));
    if (ptr == NULL)
    {
        printf("not able to push the element");
    }
    else
    {
        char *token;

        token = strtok(line, ",");
        // printf("%s", token);
        int i = 1;
        while (token != NULL)
        {
            if (i == 1)
            {
                i++;
                ptr->srNo = atoi(token);
            }
            else if (i == 2)
            {
                i++;
                strcpy(ptr->proName, token);
            }
            else if (i == 3)
            {
                i++;
                ptr->price = atoi(token);
            }
            else if (i == 4)
            {
                i++;
                ptr->quan = atoi(token);
            }
            else if (i == 5)
            {

                strcpy(ptr->preference, token);
            }
            // The first call to strtok must pass the C string to tokenize, and subsequent calls must specify NULL as the first argument, which tells the function to continue tokenizing the string you passed in first.

            token = strtok(NULL, ",");
        }
        // printf("\n");
    }
    if (head == NULL)
    {

        ptr->next = NULL;
        head = ptr;
    }
    else
    {

        ptr->next = head;
        head = ptr;
    }
    printf("Item pushed");
}
void display()
{

    struct node *ptr;
    ptr = head;
    if (ptr == NULL)
    {
        printf("Stack is empty\n");
    }
    else
    {
        printf("Printing Stack elements \n");
        while (ptr != NULL)
        {
            printf("%d %s\n", ptr->srNo, ptr->proName);
            ptr = ptr->next;
        }
    }
}
int main()
{
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
        printf("\n");
    }
    display();
}
