#include "restaurant.h"

struct node *head, *veg_head, *nveg_head;

void pushing(int s_no, char name[50], int price, int quant, char type, int profit)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->quan = quant;
    new_node->srNo = s_no;
    strcpy(new_node->proName, name);
    new_node->price = price;
    new_node->preference = type;
    new_node->profit = profit;
    if (type == 'V')
    {
        new_node->next = veg_head;
        veg_head = new_node;
    }
    else if (type == 'N')
    {
        new_node->next = nveg_head;
        nveg_head = new_node;
    }
}

int ll_length(struct node *temp_head)
{
    int n = 0;
    struct node *p = temp_head;
    while (p != NULL)
    {
        n++;
        p = p->next;
    }
    return n;
}

void create_list()
{
    struct node *temp = head;
    while (temp != NULL)
    {
        if (temp->preference == 'V')
        {
            pushing(temp->srNo, temp->proName, temp->price, temp->quan, temp->preference, temp->profit);
        }
        else if (temp->preference == 'N')
        {
            pushing(temp->srNo, temp->proName, temp->price, temp->quan, temp->preference, temp->profit);
        }
        temp = temp->next;
    }
}

int *convArrayPrice(struct node *temp_head)
{
    struct node *temp = temp_head;
    int len = ll_length(temp);
    int *arr = malloc(sizeof(int) * len);
    ;
    int i = 0;
    while (temp != NULL)
    {
        arr[i] = temp->price;
        i++;
        temp = temp->next;
    }
    return arr;
}

int *convArrayProfit(struct node *temp_head)
{
    struct node *temp = temp_head;
    int len = ll_length(temp);
    int *arr = malloc(sizeof(int) * len);
    int i = 0;
    while (temp != NULL)
    {
        arr[i] = temp->profit;
        i++;
        temp = temp->next;
    }

    return arr;
}
int maxm(int a, int b) { return (a > b) ? a : b; }

void knapSack(int budget, int price[], int profit[], int n, struct node *final)
{
    struct node *tempro = final;
    int i, w;
    int K[n + 1][budget + 1];
    for (i = 0; i <= n; i++)
    {
        for (w = 0; w <= budget; w++)
        {
            if (i == 0 || w == 0)
                K[i][w] = 0;
            else if (price[i - 1] <= w)
                K[i][w] = maxm(profit[i - 1] + K[i - 1][w - price[i - 1]], K[i - 1][w]);
            else
                K[i][w] = K[i - 1][w];
        }
    }

    int res = K[n][budget];

    w = budget;
    printf("=====================================================================================\n");
    printf("\t\t\t\tORDER THIS FOR BEST TASTE\n");
    printf("=====================================================================================\n");
    for (i = n; i > 0 && res > 0; i--)
    {
        if (res == K[i - 1][w])
            continue;
        else
        {

            while (tempro != NULL)
            {
                if (price[i - 1] == tempro->price)
                {
                    printf("Serial no:%d\t Product Name:%s\t Price:%d\t Prefernce:%c\t  \n", tempro->srNo, tempro->proName, tempro->price, tempro->preference);
                }
                tempro = tempro->next;
            }
            tempro = final;
            res = res - profit[i - 1];
            w = w - price[i - 1];
        }
    }
}
void greetings() // Exit Screen
{

    printf("\n\t\t\t\tThank You Very Much\n ");
    printf("=====================================================================================\n");
    printf("\t\t\t\t Please come again\n\n");
}

void generate_bill(struct node *temp)
{

    struct node *p = temp;
    int no_of_orders;
    printf("=====================================================================================\n");
    printf("HOW MANY ITEMS DO YOU WANT TO ORDER?: ");
    scanf("%d", &no_of_orders);
    printf("=====================================================================================\n");
    int serial_no[no_of_orders];
    printf("ENTER THE SERIAL NUMBERS OF ITEMS TO BE ORDERED\n");
    printf("=====================================================================================\n");
    for (int i = 0; i < no_of_orders; i++)
    {
        printf("ENTER ORDER %d SERIAL NUMBER: ", i + 1);
        scanf("%d", &serial_no[i]);
    }
    int sum = 0;
    printf("\n\n\n\n\n=====================================================================================\n");
    printf("\t\t\t\tTOTAL BILL\n");
    printf("=====================================================================================\n");
    for (int j = 0; j < no_of_orders; j++)
    {
        while (p != NULL)
        {
            if (p->srNo == serial_no[j])
            {
                printf("ITEM %d: %s\tPRICE: %d\n", j + 1, p->proName, p->price);
                sum += p->price;
            }
            p = p->next;
        }
        p = temp;
    }
    printf("\nTOTAL PRICE:\t%d", sum);
}

int main()
{
    struct node *temp;
    int *priceArr, *profitArr;
    int budget_amount;
    char choice;
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
    }
    printf("\n============================================================= Welcome to CHIP ‘n’ DALE =============================================================\n");
    int ch;

    printf("Available choices : \n");
    printf("1-->Login as admin\n");
    printf("2-->Login as customer\n");
    printf("3-->Exit from program\n");
    printf("\n");
    printf("Please enter your choice : ");
    scanf("%d", &ch);
    printf("\n");
    switch (ch)
    {
    case 1:
        MergeSort(&head);
        display();
        break;
    case 2:

        printf("DO YOU WANT VEG OR NON-VEG FOOD?[V/N]: ");
        scanf(" %c", &choice);

        if (choice == 'V')
        {
            create_list();
            temp = veg_head;
            priceArr = convArrayPrice(veg_head);
            profitArr = convArrayProfit(veg_head);
        }
        else if (choice == 'N')
        {

            create_list();
            temp = nveg_head;
            priceArr = convArrayPrice(nveg_head);
            profitArr = convArrayProfit(nveg_head);
        }

        printf("ENTER YOUR BUDGET AMOUNT: ");
        scanf("%d", &budget_amount);

        knapSack(budget_amount, priceArr, profitArr, 5, temp);
        generate_bill(head);
        break;
    case 3:
        printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx Exiting Now xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
        break;
    default:
        printf("Enter the correct choice\n");
    }
    greetings();
    return 0;
}
