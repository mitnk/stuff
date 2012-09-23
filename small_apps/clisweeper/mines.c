#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mines.h"

void get_random_x_y(int *x, int *y)
{
    *x = (char)(drand48() * 10);
    *y = (char)(drand48() * 10);
}

void print_mines(struct stone mines[][10], int show_all)
{
    int x = 0;
    int y = 0;
    printf("\n");
    for (y = 0; y < 10; ++y)
    {
        for (x = 0; x < 10; ++x)
        {
            if (mines[x][y].is_open)
            {
                if (mines[x][y].value == -1)
                    printf("x ");
                else
                    printf("%d ", mines[x][y].value);
            }
            else
            {
                if (mines[x][y].value == -1 && show_all == 1)
                    printf("x ");
                else
                    printf("■ ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void init_mines(struct stone mines[][10])
{
    int x = 0;
    int y = 0;
    for (x = 0; x < 10; ++x)
    {
        for (y = 0; y < 10; ++y)
        {
            mines[x][y].is_open = 0;
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

int count_number(struct stone mines[][10], int x, int y)
{
    // 数一数周围八个点有几个雷
    int sum = 0;
    int offset_x, offset_y;
    for (offset_x = -1; offset_x <= 1; ++offset_x)
    {
        for (offset_y = -1; offset_y <= 1; ++offset_y)
        {
            if (x + offset_x >= 0 && x + offset_x <= 9 &&
                y + offset_y >= 0 && y + offset_y <= 9)
            {
                if (mines[x + offset_x][y + offset_y].value == -1)
                    sum += 1;
            }
        }
    }
    return sum;
}

int check_stone(struct stone mines[][10], int x, int y)
{
    if (mines[x][y].is_open)
    {
        return ERROR_ALREADY_OPENED;
    }
    else if (mines[x][y].value == -1)
    {
        return ERROR_MINE;
    }
    else
    {
        mines[x][y].value = count_number(mines, x, y);
        mines[x][y].is_open = 1;
        return 0;
    }
    return 0;
}