#include <stdio.h>
#include "mines.h"

int main()
{
    struct stone mines[10][10];
    init_mines(mines);
    place_mines(mines);
    print_mines(mines);

    int x, y;
    while (1)
    {
        scanf("%d", &x);
        scanf("%d", &y);
        check_mine(x, y);
        print_mines(mines);
    }
}
