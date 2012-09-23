#define ERROR_MINE 1
#define ERROR_ALREADY_OPENED 2

struct stone {
    char is_open;
    char value;
};

void init_mines(struct stone mines[][10]);
void place_mines(struct stone mines[][10]);
void print_mines(struct stone mines[][10], int show_all);
int check_stone(struct stone mines[][10], int x, int y);
