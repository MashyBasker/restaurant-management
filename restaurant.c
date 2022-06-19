#include <stdio.h>
#include <stdlib.h>
#include <string.h>

skip_line(FILE *fp)
{
    int c;

    while (c = fgetc(fp), c != '\n' && c != EOF)
        ;

    return c;
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

        char *token;

        token = strtok(line, ",");
        // printf("%s", token);

        while (token != NULL)
        {
            printf("%-12s", token);
            // The first call to strtok must pass the C string to tokenize, and subsequent calls must specify NULL as the first argument, which tells the function to continue tokenizing the string you passed in first.

            token = strtok(NULL, ",");
        }
        printf("\n");
    }
}
