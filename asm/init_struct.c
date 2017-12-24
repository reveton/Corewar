#include "asm.h"

void	init_struct(t_asm **asem)
{
    t_asm *tmp;

    tmp = (t_asm*)malloc(sizeof(t_asm));
    tmp->comment = 0;
    tmp->magic[4] = NULL;
    tmp->prog_name = 0;
    tmp->prog_size = 0;
    tmp->commands = 0;
    tmp->print = 0;
    *asem = tmp;
}