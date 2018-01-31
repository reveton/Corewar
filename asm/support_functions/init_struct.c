#include "../asm.h"

void	init_struct(t_asm **asem)
{
    t_asm *tmp;

    tmp = (t_asm*)malloc(sizeof(t_asm));
    tmp->comment = 0;
    tmp->prog_name = 0;
    tmp->prog_size = 0;
    tmp->commands = 0;
    tmp->print = 0;
    tmp->com = 0;
    tmp->k = 0;
    tmp->issetcomment = 0;
    tmp->issetname = 0;
    tmp->found_label = 0;
    tmp->tmp = 0;
    tmp->tmp_ska = 0;
    tmp->grace = 2;
    *asem = tmp;
}

t_operation	*init_struct_operation(void)
{
    t_operation	*commands;

    commands = (t_operation *)malloc(sizeof(t_operation));
    commands->args = NULL;
    commands->label = NULL;
    commands->command_name = NULL;
    commands->index = -1;
    commands->count_args = 0;
    commands->check_end = 0;
    commands->len = 0;
    return (commands);
}
