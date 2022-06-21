#include <stdio.h>
#include "restaurant.h"
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
        // printf("\n");
    }

    MergeSort(&head);
    display();
}
