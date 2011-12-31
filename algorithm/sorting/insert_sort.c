#include <stdio.h>

void insert_sort(int [], int);

int main()
{
    int a[5] = {2, 3, 8, 6, 1};
    printf("%d\n", insert_sort(a, 5));
    int i;
    for (i = 0; i < 5; ++i)
        printf("%d ", a[i]);
    printf("\n");
}

void insert_sort(int a[], const int size)
{
    int i, j, key;
    for (j = 1; j < size; ++j)
    {
        key = a[j];
        i = j - 1;
        while (i >= 0 && a[i] > key)
            a[i+1] = a[i--];
        a[i+1] = key;
    }
}
