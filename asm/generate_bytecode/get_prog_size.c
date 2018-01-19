#include "../asm.h"

void	get_command_len(int op_index, t_asm *content)
{
    int j;
    int	arg;

    j = 0;
    while (content->commands[op_index]->args[j])
    {
        arg = check_type_arg(content->commands[op_index]->args[j]);
        if (arg == T_REG)
            content->commands[op_index]->len++;
        else if ((arg == T_IND)
                 || (arg == T_LAB
                     && content->commands[op_index]->args[j][0] != DIRECT_CHAR))
            content->commands[op_index]->len += 2;
        else if (arg == T_DIR || arg == T_LAB)
        {
            if (!g_op_tab[content->commands[op_index]->index].label_size)
                content->commands[op_index]->len += 2;
            content->commands[op_index]->len += 2;
        }
        j++;
    }
}

void		get_prog_len(t_asm *content)
{
    int	i;

    i = 0;
    while (content->commands[i] && !content->commands[i]->check_end)
    {
        content->commands[i]->len = 1;
        if (g_op_tab[content->commands[i]->index].octal_coding)
            content->commands[i]->len++;
        get_command_len(i, content);
        i++;
    }
}

void    get_prog_size(t_asm *asem)
{
    int i;

    i = 0;
    while (asem->commands[i] && !asem->commands[i]->check_end)
    {
        asem->prog_size += asem->commands[i]->len;
        i++;
    }
}