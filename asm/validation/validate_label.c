#include "../asm.h"

static int    check_label(t_asm *asem, char *str)
{
    int i;
    int j;

    if (str[0] == DIRECT_CHAR)
        str = str + 2;
    else
        str = str + 1;
    i = 0;
    while (asem->commands && asem->commands[i])
    {
        j = 0;
        while (asem->commands[i]->label && asem->commands[i]->label[j])
        {
            if (ft_strequ(asem->commands[i]->label[j], str))
                return (1);
            j++;
        }
        i++;
    }
    return (0);
}

void    check_exist_label(t_operation *commands, t_asm *asem)
{
    int i;

    i = 0;
    if (commands->args) {
        while (commands->args[i]) {
            if (is_label(commands->args[i]))
            {
                if (!check_label(asem, commands->args[i]))
                {
                    ft_printf("***--->[%s]<---***\n", commands->args[i]);
                    ft_put_error("Invalid label");
                }
            }
            i++;
        }
    }
}
