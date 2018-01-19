#include "../asm.h"

int			asm_label_len(t_asm *content, char *label, int index)
{
    int	index2;

    index2 = get_label_position(content, label);
    if (index2 > index)
        return (get_label_len_between(content, index, index2));
    else if (index2 < index)
        return (-get_label_len_between(content, index2, index));
    else
        return (0);
}

int    get_t_dir(t_asm *asem, int i, int c, int a)
{
    unsigned int n;
    int type;

    type = check_type_arg(asem->commands[i]->args[a]);
    if (type == T_LAB)
        n = (unsigned int)asm_label_len(asem, asem->commands[i]->args[a] + 2, i);
    else
        n = (unsigned int)ft_atoi(asem->commands[i]->args[a] + 1);
    if (g_op_tab[asem->commands[i]->index].label_size)
        n = (unsigned short) n;
    if (!g_op_tab[asem->commands[i]->index].label_size)
    {
        asem->commands[i]->coding_string[c++] = (unsigned char)((n >> 24) & 0xFF);
        asem->commands[i]->coding_string[c++] = (unsigned char)((n >> 16) & 0xFF);
    }
    asem->commands[i]->coding_string[c++] = (unsigned char)((n >> 8) & 0xFF);
    asem->commands[i]->coding_string[c++] = (unsigned char)(n & 0xFF);
    return (c);
}

int    get_indir(t_asm *asem, int i, int c, int a)
{
    unsigned int n;
    int type;

    type = check_type_arg(asem->commands[i]->args[a]);
    if (type == T_LAB)
        n = (unsigned short)asm_label_len(asem, asem->commands[i]->args[a] + 1, i);
    else
        n = (unsigned int)ft_atoi(asem->commands[i]->args[a]);
    asem->commands[i]->coding_string[c++] = (unsigned char)((n >> 8) & 0xFF);
    asem->commands[i]->coding_string[c++] = (unsigned char)(n & 0xFF);
    return (c);
}

