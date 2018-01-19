#include "../asm.h"

static int     get_count_args(t_operation *commands)
{
    int i;

    i = 0;
    if (commands->args)
    {
        while (commands->args[i])
            i++;
    }
    return (i);
}

void    validate_count_args(t_operation *commands)
{
    unsigned int count_args;

    count_args = (unsigned int) get_count_args(commands);
    if (count_args != g_op_tab[commands->index].count_args)
    {
        ft_printf("***--->[%s]<---***\n", commands->command_name);
        ft_put_error("Invalid count args for instruction");
    }
}

int    check_type_arg(char *str)
{
    if (is_register(str))
        return (T_REG);
    if (is_dir(str))
        return (T_DIR);
    if (is_indir(str))
        return (T_IND);
    if (is_label(str))
        return (T_LAB);
    return (-1);
}

void    validate_type_args(t_operation *commands)
{
    int i;
    int type;

    i = 0;
    if (commands->args)
    {
        while (commands->args[i]) {
            type = check_type_arg(commands->args[i]);
            if (!check_conformity(commands->args[i], type, commands, i)) {
                ft_printf("***--->[%s]<---***\n", commands->args[i]);
                ft_put_error("Invalid arguments");
            }
            if (type == -1) {
                ft_printf("***--->[%s]<---***\n", commands->args[i]);
                ft_put_error("Invalid argument type");
            }
            i++;
        }
    }
}