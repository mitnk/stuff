#include <stdio.h>

void print_array(int a[], const int size);

int main()
{
    int a[10] = { 5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
    print_array(a, 10);

    int b[10] = { 5, 5 };
    print_array(b, 10);

    int c[10] = { 0 };
    print_array(c, 10);

    static int s[10];
    print_array(s, 10);

    // GCC only
    int d[30] = {[0 ... 9] = 5, [20 ... 29] = 3};
    print_array(d, 30);
}

void print_array(int a[], const int size)
{
    int i;
    for (i = 0; i < size; ++i)
        printf("%d ", a[i]);
    printf("\n");
}
