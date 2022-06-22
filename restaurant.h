#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct node
{
    int srNo, quan, price;
    char proName[50];
    char preference;
    int profit;
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
                i++;
                ptr->preference = *token;
            }
            else if (i == 6)
                ptr->profit = atoi(token);
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

struct node *SortedMerge(struct node *a, struct node *b)
{
    struct node *result = NULL;

    /* Base cases */
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);

    /* Pick either a or b, and recur */
    if (a->quan >= b->quan)
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
        printf("-------------------------TODAY'S MENU TO BE PREPARED------------------------- \n");
        while (ptr != NULL)
        {
            printf("%d\t %s\t %d\t %d\t %c\t %d\t \n", ptr->srNo, ptr->proName, ptr->price, ptr->quan, ptr->preference, ptr->profit);
            ptr = ptr->next;
        }
    }
}
