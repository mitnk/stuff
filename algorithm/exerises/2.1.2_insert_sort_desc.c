#include <stdio.h>

void insert_sort_desc(int a[], const int size)
{
    int i, j, key;
    for (i = 1; i < size; ++i)
    {
        key = a[i];
        j = i - 1;
        while (j >= 0 && a[j] < key)
        {
            a[j + 1] = a[j];
            --j;
        }
        a[j + 1] = key;
    }
}

int main()
{
    int a[] = {31, 41, 59, 26, 41, 58};
    insert_sort_desc(a, 6);
    int i;
    for (i = 0; i < 6; ++i)
        printf("%d ", a[i]);
    printf("\n");
}
