#define ERROR_MINE 1
#define ERROR_ALREADY_OPENED 2
#define FINISHED 10

#define X 10
#define Y 10
#define MINES 10

struct stone {
    char is_open;
    char value;
};

void init_mines(struct stone mines[][Y]);
void place_mines(struct stone mines[][Y]);
void print_mines(struct stone mines[][Y], int show_all);
int check_stone(struct stone mines[][Y], int x, int y);
