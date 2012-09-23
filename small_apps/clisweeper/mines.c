#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mines.h"

void get_random_x_y(int *x, int *y)
{
    *x = (char)(drand48() * 10);
    *y = (char)(drand48() * 10);
}

void print_mines(struct stone mines[][10])
{
    int x = 0;
    int y = 0;
    for (x = 0; x < 10; ++x)
    {
        for (y = 0; y < 10; ++y)
        {
            if (mines[x][y].is_open)
            {
                if (mines[x][y].value == -1)
                    printf("x ");
                else
                    printf("%d ", mines[x][y].value);
            }
            else
                printf("■ ");
        }
        printf("\n");
    }
}

void init_mines(struct stone mines[][10])
{
    int x = 0;
    int y = 0;
    for (x = 0; x < 10; ++x)
    {
        for (y = 0; y < 10; ++y)
        {
            mines[x][y].is_open = 1;
            mines[x][y].value = 0;
        }
    }
}

void place_mines(struct stone mines[][10])
{
    int x = 0;
    int y = 0;
    int i = 0;
    srand48(time(0));
    for (i = 0; i < 10; ++i)
    {
        get_random_x_y(&x, &y);
        if (mines[x][y].value == -1)
        {
            --i;
            continue;
        }
        else
        {
            mines[x][y].value = -1;
        }
    }
}

void check_stone(struct stone mines[][10], x, y)
{
    int x = 0;
    int y = 0;
    int i = 0;
    srand48(time(0));
    for (i = 0; i < 10; ++i)
    {
        get_random_x_y(&x, &y);
        if (mines[x][y].value == -1)
        {
            --i;
            continue;
        }
        else
        {
            mines[x][y].value = -1;
        }
    }
}
