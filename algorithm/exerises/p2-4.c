#include <stdio.h>
#include <string.h>

int merge(int a[], int b[], int left, int mid, int right)
{
    int count = 0;
    int i, j, k;
    k = 0;
    j = left;
    while (j <= mid)
        b[k++] = a[j++];

    i = 0;
    k = left;
    while (k < j && j <= right)
        if (b[i] <= a[j])
            a[k++] = b[i++];
        else
        {
            count += (j - k);
            a[k++] = a[j++];
        }

    while (k < j)
    {
        a[k++] = b[i++];
    }
    return count;
}

int merge_sort(int a[], int b[], int left, int right)
{
    if (left >= right)
        return 0;
    int mid = (left + right) / 2;
    int i = merge_sort(a, b, left, mid);
    int j = merge_sort(a, b, mid + 1, right);
    return i + j + merge(a, b, left, mid, right);
}

int main()
{
    int b[5] = {2, 3, 8, 6, 1};
    int b1[3] = {0};
    printf("count: %d\n", merge_sort(b, b1, 0, 4));

    int a[10] = {1, 7, 3, 4, 9, 0, 5, 6, 2, 8};
    int a1[5] = {0};
    printf("count: %d\n", merge_sort(a, a1, 0, 9));
}

