#include <stdio.h>

int get_input()
{
    int n;
    int num;
    do
    {
        printf("Number: ");
        num = scanf("%d", &n);

        if (num != 1)
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
            {
            }
        }
    }
    while (num != 1);
    return n;
}