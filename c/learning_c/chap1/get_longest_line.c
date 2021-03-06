#include <stdio.h>
#define MAX 1000

int get_line(char line[], int maxline);
void copy(char to[], char from[]);

main()
{
    int len;
    int max = 0;
    char line[MAX];
    char longest[MAX];

    while((len = get_line(line, MAX)) > 0)
        if (len > max) {
            max = len;
            copy(longest, line);
        }

    if (max > 0)
        printf("%s\n", longest);
    return 0;
}

int get_line(char line[], int maxline)
{
    int c, i;

    for (i=0; i<maxline && (c=getchar()) != EOF && c != '\n'; ++i)
        line[i] = c;
    if (c == '\n') {
        line[i] = c;
        ++i;
    }
    line[i] = '\0';
    return i;
}


void copy(char to[], char from[])
{
    int i = 0;
    while((to[i] = from[i]) != '\0')
        ++i;
}
