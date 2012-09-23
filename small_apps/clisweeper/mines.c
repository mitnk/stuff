#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mines.h"

void get_random_x_y(int *x, int *y)
{
    *x = (char)(drand48() * X);
    *y = (char)(drand48() * Y);
}

void print_mines(struct stone mines[][Y], int show_all)
{
    int x = 0;
    int y = 0;
    printf("\n■ x ");
    for (x = 0; x < X; ++x)
        printf("%d ", x);
    printf("\ny\n");
    for (y = 0; y < Y; ++y)
    {
        printf("%d   ", y);
        for (x = 0; x < X; ++x)
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

void init_mines(struct stone mines[][Y])
{
    int x = 0;
    int y = 0;
    for (x = 0; x < X; ++x)
    {
        for (y = 0; y < Y; ++y)
        {
            mines[x][y].is_open = 0;
            mines[x][y].value = 0;
        }
    }
}

void place_mines(struct stone mines[][Y])
{
    int x = 0;
    int y = 0;
    int i = 0;
    srand48(time(0));
    for (i = 0; i < MINES; ++i)
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

void open_around_stones(struct stone mines[][Y], int x, int y)
{
    int offset_x, offset_y;
    int sum = 0;
    for (offset_x = -1; offset_x <= 1; ++offset_x)
    {
        for (offset_y = -1; offset_y <= 1; ++offset_y)
        {
            if (offset_x == 0 && offset_y == 0)
                continue;


            if (x + offset_x >= 0 && x + offset_x < X &&
                y + offset_y >= 0 && y + offset_y < Y &&
                mines[x + offset_x][y + offset_y].is_open == 0)
            {
                sum = count_number(mines, x + offset_x, y + offset_y);
                if (sum == 0)
                    open_around_stones(mines, x + offset_x, y + offset_y);
            }
        }
    }
}

int count_number(struct stone mines[][Y], int x, int y)
{
    // 数一数周围八个点有几个雷
    int sum = 0;
    int offset_x, offset_y;
    for (offset_x = -1; offset_x <= 1; ++offset_x)
    {
        for (offset_y = -1; offset_y <= 1; ++offset_y)
        {
            if (x + offset_x >= 0 && x + offset_x < X &&
                y + offset_y >= 0 && y + offset_y < Y)
            {
                if (mines[x + offset_x][y + offset_y].value == -1)
                    sum += 1;
            }
        }
    }
    mines[x][y].value = sum;
    mines[x][y].is_open = 1;
    return sum;
}

int is_finished(struct stone mines[][Y])
{
    int x = 0;
    int y = 0;
    int sum = 0;
    for (y = 0; y < Y; ++y)
    {
        for (x = 0; x < X; ++x)
        {
            if (!mines[x][y].is_open)
                ++sum;
        }
    }
    return sum == MINES;
}

int check_stone(struct stone mines[][Y], int x, int y)
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
        int result = count_number(mines, x, y);
        if (result == 0)
        {
            open_around_stones(mines, x, y);
        }
        if (is_finished(mines))
            return FINISHED;
        return 0;
    }
    return 0;
}
