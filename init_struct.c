#include "asm.h"

void	init_struct(t_asm **asem)
{
    t_asm *tmp;

    tmp = (t_asm*)malloc(sizeof(t_asm));
    tmp->comment = 0;
    tmp->magic = 0;
    tmp->prog_name = 0;
    tmp->prog_size = 0;
    tmp->commands = 0;
    *asem = tmp;
}