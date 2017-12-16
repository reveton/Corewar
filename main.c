#include "asm.h"

void    detailed_print(t_asm *asem)
{
    int i;
    int j;

    i = 0;
    ft_printf("Name : \"%s\"\n", asem->prog_name);
    ft_printf("Comment : \"%s\"\n", asem->comment);
    while (asem->commands[i])
    {
        j = 0;
        while (asem->commands[i]->label && asem->commands[i]->label[j])
            ft_printf("%s:\n", asem->commands[i]->label[j++]);
        ft_printf("\t\t%s\t->\t", asem->commands[i]->name);
        j = 0;
        while (asem->commands[i]->args[j] && asem->commands[i]->args)
        {
            ft_printf("'%s'", asem->commands[i]->args[j]);
            j++;
        }
        i++;
        ft_printf("\n");
    }
}

void    validate_commands(t_operation *commands)
{
    int i;

    i = 0;
    while (i < OP_COUNT)
    {
        if (ft_strequ(commands->name, g_op_tab[i].name))
        {
            commands->index = i;
            break ;
        }
        i++;
    }
}

void    validate_count_args(t_operation *commands)
{
    int i;

    i = 0;
    while (commands->args[i])
        i++;
    if (i > g_op_tab[commands->index].count_args)
    {
        ft_printf("***--->%s<---***\n", commands->name);
        ft_put_error("Invalid count args for instruction");
    }
    else if (i < g_op_tab[commands->index].count_args)
    {
        ft_printf("***--->%s<---***\n", commands->name);
        ft_put_error("Invalid count args for instruction");
    }
}

void    generate_bytecode(t_asm *asem)
{
    int i;

    i = 0;
    while (asem->commands[i])
    {
        validate_commands(asem->commands[i]);
        validate_count_args(asem->commands[i]);
        if (asem->commands[i]->index  == -1)
        {
            ft_printf("***--->%s<---***\n", asem->commands[i]->name);
            ft_put_error("Invalid instruction");
        }
        i++;
    }


}

int     check_filename(const char *str)
{
    int i;
    int k;

    i = 0;
    k = 0;
    while (str[i])
    {
        if (str[i] == '.')
            k = i;
        i++;
    }
    if ((str[k + 1]) != 's' || k == 0)
        return (0);
    return (1);
}

int     main(int ac, char **av)
{
    int fd;
    t_asm *asem;

    init_struct(&asem);
    fd = open(av[ac - 1], O_RDONLY);
    if (ac < 2)
        error_usage();
    if (!check_filename(av[ac - 1]) || fd < 0)
        error_name(av,ac);
    if (!validation(fd, 0, asem))
        ft_put_error("Validation Error");
    else
        generate_bytecode(asem);
    if (ft_strequ("-a", av[1]))
        detailed_print(asem);
}