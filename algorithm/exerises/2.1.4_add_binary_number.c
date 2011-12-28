#include <stdio.h>

void add_binary(int a[], int b[], int c[], const int size)
{
    int overflow = 0;
    int result;
    int i;
    for (i = size - 1; i >= 0; --i)
    {
        result = a[i] + b[i] + overflow;
        if (result == 3)
        {
            c[i + 1] = 1;
            overflow = 1;
        }
        else if (result == 2)
        {
            c[i + 1] = 0;
            overflow = 1;
        }
        else if (result == 1)
        {
            c[i + 1] = 1;
            overflow = 0;
        }
    }
    c[0] = overflow;
}

int main()
{
    int a[] = {1, 1, 0, 1, 0, 1, 1, 1};
    int b[] = {0, 1, 0, 0, 1, 1, 0, 1};
    int c[9] = {0};
    add_binary(a, b, c, 8);
    int i;
    printf("  ");
    for (i = 0; i < 8; ++i)
        printf("%d ", a[i]);
    printf("\n");
    printf("  ");
    for (i = 0; i < 8; ++i)
        printf("%d ", b[i]);
    printf("\n");
    for (i = 0; i < 9; ++i)
        printf("%d ", c[i]);
    printf("\n");
}
