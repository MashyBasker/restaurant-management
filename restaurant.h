#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct node
{
    int sr_no, prod_quant_sold, prod_price;
    char prod_name[50];
    char prod_type;
    struct node *next;
}node;

int size = 0;
node *head;

int skip_line(FILE *fp)
{
    int c;

    while (c = fgetc(fp), c != '\n' && c != EOF)
        ;

    return c;
}

// void create_menu_list() {
//     int no_items , item_price , items_sold;
//     char item_name[50] , item_type;
//     printf("HOW MANY ITEMS ARE PRESENT IN THE MENU: ");
//     scanf("%d" , &no_items);
//     for (int i = 0 ; i < no_items ; i++) {
//         printf("ENTER THE NAME OF THE ITEM %d: " , i + 1);
//         scanf("%s" , &item_name);
//         printf("ENTER THE PRICE OF THE ITEM %d: " , i + 1);
//         scanf("%d" , &item_price);
//         printf("ENTER THE TYPE OF THE ITEM %d [V/N]: " , i + 1);
//         scanf(" %c" , &item_type);
//         printf("ENTER THE NO. OF ITEM %d SOLD IN PAST WEEK: " , i + 1);
//         scanf("%d" , &items_sold);
//         push_back(item_name , item_price , items_sold , item_type);
//     }
// }

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
                ptr->sr_no = atoi(token);
            }
            else if (i == 2)
            {
                i++;
                strcpy(ptr->prod_name, token);
            }
            else if (i == 3)
            {
                i++;
                ptr->prod_price = atoi(token);
            }
            else if (i == 4)
            {
                i++;
                ptr->prod_quant_sold = atoi(token);
            }
            else if (i == 5)
            {

                strcpy(ptr->prod_type, token);
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
    // printf("Item pushed");
}

/* function prototypes */
struct node *SortedMerge(struct node *a, struct node *b);
void FrontBackSplit(struct node *source,
                    struct node **frontRef, struct node **backRef);

/* sorts the linked list by changing next pointers (not data) */
void MergeSort(struct node **headRef)
{
    struct node *head1 = *headRef;
    struct node *a;
    struct node *b;

    /* Base case -- length 0 or 1 */
    if ((head1 == NULL) || (head1->next == NULL))
    {
        return;
    }

    /* Split head into 'a' and 'b' sublists */
    FrontBackSplit(head1, &a, &b);

    /* Recursively sort the sublists */
    MergeSort(&a);
    MergeSort(&b);

    /* answer = merge the two sorted lists together */
    *headRef = SortedMerge(a, b);
}

/* See https:// www.geeksforgeeks.org/?p=3622 for details of this
function */
struct node *SortedMerge(struct node *a, struct node *b)
{
    struct node *result = NULL;

    /* Base cases */
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);

    /* Pick either a or b, and recur */
    if (a->prod_quant_sold >= b->prod_quant_sold)
    {
        result = a;
        result->next = SortedMerge(a->next, b);
    }
    else
    {
        result = b;
        result->next = SortedMerge(a, b->next);
    }
    return (result);
}

/* UTILITY FUNCTIONS */
/* Split the nodes of the given list into front and back halves,
    and return the two lists using the reference parameters.
    If the length is odd, the extra node should go in the front list.
    Uses the fast/slow pointer strategy. */
void FrontBackSplit(struct node *source,
                    struct node **frontRef, struct node **backRef)
{
    struct node *fast;
    struct node *slow;
    slow = source;
    fast = source->next;

    /* Advance 'fast' two nodes, and advance 'slow' one node */
    while (fast != NULL)
    {
        fast = fast->next;
        if (fast != NULL)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }

    /* 'slow' is before the midpoint in the list, so split it in two
    at that point. */
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
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
        printf("-----------------TODAYS MENU TO BE PREPARED------------------------- \n");
        while (ptr != NULL)
        {
            printf("%d %s %d %d %s \n", ptr->sr_no, ptr->prod_name, ptr->prod_price, ptr->prod_quant_sold, ptr->prod_type);
            ptr = ptr->next;
        }
    }
}
