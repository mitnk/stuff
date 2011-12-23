#include <stdio.h>

#define swap(a, b) int tmp = a; a = b; b = tmp;

void insert_sort(int [], int);
void insert_sort2(int [], int);

int main()
{
    int a[10] = {1, 7, 3, 4, 9, 0, 5, 6, 2, 8};
    insert_sort(a, 10);
    int i;
    for (i = 0; i < 10; ++i)
        printf("%d ", a[i]);
    printf("\n");

    // GCC required
    int b[10000] = {[0 ... 9] = 9, [990 ... 999] = 1, [9990 ... 9999] = 2};
    insert_sort(b, 10000);

    for (i = 9999; 9999 - i < 32; --i)
        printf("%d ", b[i]);
    printf("\n");
}

// Bad version
void insert_sort(int a[], const int size)
{
    int i, j, k;
    for (i=1; i < size; ++i)
    {
        k = i;
        for (j=i-1; j >= 0; --j)
        {
            if (a[k] < a[j])
            {
                swap(a[k], a[j]);
                k = j;
            }
        }
    }
}

// Academic version
void insert_sort2(int a[], const int size)
{
    int i, j, key;
    for (j = 1; j < size; ++j)
    {
        key = a[j];
        i = j - 1;
        while (i >= 0 && a[i] > key)
        {
            a[i + 1] = a[i];
            i -= 1;
        }
        a[i + 1] = key;
    }
}
