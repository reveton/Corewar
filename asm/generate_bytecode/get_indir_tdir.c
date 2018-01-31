#include "../asm.h"

int         l_length(t_asm *asem, char *label, int i)
{
    int	start;

    start = get_pos(asem, label, 0, 0);
    if (start > i)
        return (distance(asem, i, start, 0));
    else if (start < i)
        return (-distance(asem, start, i, 0));
    else
        return (0);
}

int    get_t_dir(t_asm *asem, int i, int v, int a)
{
    unsigned int n;
    int type;
    int bytes;

    bytes = 24;
    type = check_type_arg(asem->commands[i]->args[a]);
    if (check_arg(4, type))
        n = (unsigned int)l_length(asem, asem->commands[i]->args[a] + 2, i);
    else
        n = (unsigned int)ft_atoi(asem->commands[i]->args[a] + 1);
    if (g_op_tab[asem->commands[i]->index].label_size)
        n = (unsigned short) n;
    if (!g_op_tab[asem->commands[i]->index].label_size)
    {
        asem->commands[i]->coding_string[v++] = (unsigned char)((n >> bytes) & 0xFF);
        bytes -= 8;
        asem->commands[i]->coding_string[v++] = (unsigned char)((n >> bytes) & 0xFF);
    }
    bytes = 8;
    asem->commands[i]->coding_string[v++] = (unsigned char)((n >> bytes) & 0xFF);
    asem->commands[i]->coding_string[v++] = (unsigned char)(n & 0xFF);
    return (v);
}

int    get_indir(t_asm *asem, int i, int v, int a)
{
    unsigned int n;
    int type;

    type = check_type_arg(asem->commands[i]->args[a]);
    if (!check_arg(4, type))
        n = (unsigned int)ft_atoi(asem->commands[i]->args[a]);
    else
        n = (unsigned short)l_length(asem, asem->commands[i]->args[a] + 1, i);
    asem->commands[i]->coding_string[v++] = (unsigned char)((n >> 8) & 0xFF);
    asem->commands[i]->coding_string[v++] = (unsigned char)(n & 0xFF);
    return (v);
}

