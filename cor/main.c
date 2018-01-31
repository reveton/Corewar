#include "cor.h"

int main(int ac, char **av)
{
    ac = 0;
    t_cor *cor;

    init_struct(&cor);
    parse_arg(av, cor);
    fill_arena(cor);
    init_cursor(cor, 0, 0);
    if (cor->n == 1)
        init_ncurses(cor, &cor->print);
    corewar(cor);
}