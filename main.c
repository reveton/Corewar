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
            ft_printf("[%s]", asem->commands[i]->args[j]);
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
        ft_printf("***--->[%s]<---***\n", commands->name);
        ft_put_error("Invalid count args for instruction");
    }
    else if (i < g_op_tab[commands->index].count_args)
    {
        ft_printf("***--->[%s]<---***\n", commands->name);
        ft_put_error("Invalid count args for instruction");
    }
}

int	is_register(char *str)
{
    if (str[0] != 'r' || !ft_isdigit(str[1]))
        return (0);
    if (!str[2])
        return (1);
    if (!ft_isdigit(str[2]) || str[3])
        return (0);
    return (1);
}

static int	is_direction(char *str)
{
    int i;

    if (str[0] != DIRECT_CHAR)
        return (0);
    i = 1;
    if (str[i] == '-')
        i++;
    if (str[0] == DIRECT_CHAR && !str[1])
        return (0);
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

static int	is_indirection(char *str)
{
    int i;

    i = 0;
    if (str[i] == '-')
        i++;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

static int	is_label(char *str)
{
    int i;

    i = 0;
    if (str[i] == DIRECT_CHAR)
        i++;
    if (str[i] != LABEL_CHAR)
        return (0);
    i++;
    while (str[i] && ft_strchr(LABEL_CHARS, str[i]))
        i++;
    if (str[i] != '\0')
        return (0);
    return (1);
}

int    check_type_arg(char *str)
{
    if (is_register(str))
        return (T_REG);
    if (is_direction(str))
        return (T_DIR);
    if (is_indirection(str))
        return (T_IND);
    if (is_label(str))
        return (T_LAB);
    return (-1);
}

int    check_comparison(char *str, int type, t_operation *commands, int i)
{
    int		arg;

    if (type == T_LAB)
        type = (str[0] == DIRECT_CHAR) ? T_DIR : T_IND;
    arg = g_op_tab[commands->index].args[i];
    if (type == T_REG)
    {
        if (arg == T_DIR || arg == T_IND || arg == (T_DIR | T_IND))
            return (0);
    }
    else if (type == T_DIR)
    {
        if (arg == T_REG || arg == T_IND || arg == (T_REG | T_IND))
            return (0);
    }
    else if (type == T_IND)
    {
        if (arg== T_DIR || arg == T_REG || arg == (T_DIR | T_REG))
            return (0);
    }
    return (1);
}

void    validate_type_args(t_operation *commands)
{
    int i;
    int type;

    i = 0;
    while (commands->args[i])
    {
        type = check_type_arg(commands->args[i]);
        if (!check_comparison(commands->args[i], type,commands,i))
        {
            ft_printf("***--->[%s]<---***\n", commands->args[i]);
            ft_put_error("Invalid arguments");
        }
        if (type == -1)
        {
            ft_printf("***--->[%s]<---***\n", commands->args[i]);
            ft_put_error("Invalid arguments");
        }
        i++;
    }
}

int    check_label(t_asm *asem, char *str)
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
    while (commands->args[i])
    {
        if (is_label(commands->args[i]))
        {
            if (!check_label(asem, commands->args[i]))
            {
                ft_printf("***--->[%s]<---***\n",commands->args[i]);
                ft_put_error("Invalid label");
            }
        }
        i++;
    }
}

void    validate_all_content(t_asm *asem, int i)
{
    validate_commands(asem->commands[i]);
    validate_count_args(asem->commands[i]);
    validate_type_args(asem->commands[i]);
    check_exist_label(asem->commands[i], asem);
}

void    generate_bytecode(t_asm *asem)
{
    int i;

    i = 0;
    while (asem->commands[i])
    {
        validate_all_content(asem,i);
        if (asem->commands[i]->index  == -1)
        {
            ft_printf("***--->[%s]<---***\n", asem->commands[i]->name);
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
        error_name(av, ac);
    if (!validation(fd, 0, asem))
        ft_put_error("Validation Error");
    else
        generate_bytecode(asem);
    if (ft_strequ("-a", av[1]))
        detailed_print(asem);
}