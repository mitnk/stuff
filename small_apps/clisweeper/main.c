#include <stdio.h>
#include "mines.h"

int main()
{
    struct stone mines[X][Y];
    init_mines(mines);
    place_mines(mines);
    print_mines(mines, 0);

    int x, y;
    int result = 0;
    while (1)
    {
        printf("Please input x y: ");
        scanf("%d", &x);
        scanf("%d", &y);
        result = check_stone(mines, x, y);
        if (result == ERROR_MINE)
        {
            printf("\n\n");
            printf("**********************\n");
            printf("* Bang!!! Game Over! *\n");
            printf("**********************\n\n");
            print_mines(mines, 1);
            break;
        }
        else if (result == ERROR_ALREADY_OPENED)
        {
            printf("=== Already Opened ===\n");
            continue;
        }
        else if (result == FINISHED)
        {
            printf("\n\n");
            printf("===========================\n");
            printf("==== Congratulation!!! ====\n");
            printf("===========================\n");
            print_mines(mines, 1);
            break;
        }
        else
        {
            printf("\n");
            printf("----------------------\n");
            printf("|     Good Job!      |\n");
            printf("----------------------\n");
        }
        print_mines(mines, 0);
    }
}
