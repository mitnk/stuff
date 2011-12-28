#include <stdio.h>
#include <string.h>

void merge(int a[], int b[], int left, int mid, int right)
{
    int i, j, k;
    j = left;
    k = mid + 1;
    for (i=left; i<=right; ++i)
    {
        if (j <= mid && k <= right)
        {
            if (a[j] > a[k])
            {
                b[i] = a[k];
                ++k;
            }
            else
            {
                b[i] = a[j];
                ++j;
            }
        }
        else if (j <= mid)
        {
            b[i] = a[j];
            ++j;
        }
        else if (k <= right)
        {
            b[i] = a[k];
            ++k;
        }
    }
    for (i=left; i<=right; ++i)
    {
        a[i] = b[i];
    }
}

void merge_sort(int a[], int b[], int left, int right)
{
    if (left >= right)
        return;
    int mid = (left + right) / 2;
    merge_sort(a, b, left, mid);
    merge_sort(a, b, mid + 1, right);
    merge(a, b, left, mid, right);
}

int main()
{
    int a[10] = {1, 7, 3, 4, 9, 0, 5, 6, 2, 8};
    int a1[10] = {0};
    merge_sort(a, a1, 0, 9);
    int i;
    for (i = 0; i < 10; ++i)
        printf("%d ", a[i]);
    printf("\n");

    // GCC required
    int b[100000] = {[0 ... 9] = 9, [990 ... 999] = 1, [99990 ... 99999] = 2};
    int b1[100000] = {0};
    merge_sort(b, b1, 0, 99999);

    for (i = 99999; 99999 - i < 32; --i)
        printf("%d ", b[i]);
    printf("\n");
}

