#include <stdio.h>

#undef get_char
#define SIZE 1024

int get_char(void)
{
    char c;
    return (read(0, &c, 1) == 1) ? (unsigned char) c : EOF;
}

void test_get_char(void)
{
    char c;
    while((c = get_char()) != EOF)
    {
        putchar(c);
    }
}

int get_char2(void)
{
    static int n = 0;
    static char buff[SIZE];
    static char *buffp = buff;
    if (n == 0)
    {
        n = read(0, buff, sizeof buff);
        buffp = buff;
    }
    return (n-- > 0) ? *buffp++ : EOF;
}

void test_get_char2(void)
{
    char c;
    while((c = get_char2()) != EOF)
    {
        putchar(c);
    }
}

int main()
{
    //printf("\nTesting getchar() ... \n");
    //test_get_char();
    printf("\nTesting getchar2() ... \n");
    test_get_char2();
}
