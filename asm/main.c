#include "asm.h"

void		asm_clean_op(t_operation *op)
{
    int	i;

    i = 0;
    while (op->label && op->label[i])
    {
        free(op->label[i]);
        i++;
    }
    if (op->label)
        free(op->label);
    i = 0;
    while (op->args && op->args[i])
    {
        free(op->args[i]);
        i++;
    }
    if (op->args)
        free(op->args);
    if (op->command_name)
        free(op->command_name);
    free(op);
}

void		asm_clean(t_asm *content)
{
    int	i;

    if (content)
    {
        if (content->prog_name)
            free(content->prog_name);
        if (content->comment)
            free(content->comment);
        if (content->file)
            free(content->file);
        i = 0;
        while (content->commands && content->commands[i])
        {
            asm_clean_op(content->commands[i]);
            i++;
        }
        if (content->commands)
            free(content->commands);
        free(content);
    }
}

void		free_str(char **str)
{
    int	i;

    i = 0;
    while (str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
}

char		*ft_joinfree(char *str1, char *str2, t_del string)
{
    char	*final;
    size_t	i;
    size_t	j;
    size_t	len;

    len = ft_strlen(str1) + ft_strlen(str2);
    if (!str1 || !str2)
        return (0);
    if (!(final = (char *)malloc(sizeof(char) * (len + 1))))
        return (0);
    i = 0;
    while (str1[i])
    {
        final[i] = str1[i];
        i++;
    }
    j = 0;
    while (str2[j])
        final[i++] = str2[j++];
    final[i] = '\0';
    if (string == BOTH || string == FIRST)
        free(str1);
    if (string == BOTH || string == SECOND)
        free(str2);
    return (final);
}

static int	check_base(const int base, char nbr)
{
    char	*basement;
    int		i;

    basement = "0123456789abcdef";
    i = 0;
    while (basement[i] && i < base)
    {
        if (basement[i] == nbr)
            return (i);
        i++;
    }
    return (-1);
}

int			ft_atoi_base(const char *str, const int base)
{
    unsigned long int	result;
    int					minus;
    size_t				i;

    i = 0;
    minus = 1;
    while (str[i] == ' ' || str[i] == '\t'
           || str[i] == '\n' || str[i] == '\v'
           || str[i] == '\f' || str[i] == '\r')
        i++;
    if (str[i] == '-')
        minus = -1;
    if (str[i] == '-' || str[i] == '+')
        i++;
    result = 0;
    while (str[i] && (check_base(base, str[i]) >= 0))
    {
        result = result * base + check_base(base, str[i]);
        i++;
    }
    return ((int)(result * minus));
}

void    detailed_print(t_asm *asem)
{
    int i;
    int c;
    int j;

    i = 0;
    ft_printf("Name : \"%s\"\n", asem->prog_name);
    ft_printf("Comment : \"%s\"\n", asem->comment);
    ft_printf("Size : \"%d bytes\"\n", asem->prog_size);
    while (asem->commands[i])
    {
        j = 0;
        while (asem->commands[i]->label && asem->commands[i]->label[j])
            ft_printf("%s:\n", asem->commands[i]->label[j++]);
        ft_printf("\t\t%s\t->\t", asem->commands[i]->command_name);
        j = 0;
        while (asem->commands[i]->args[j] && asem->commands[i]->args)
            ft_printf("'%s'", asem->commands[i]->args[j++]);
        c = 0;
        ft_printf("\t\t");
        while (c < 8)
            ft_printf("[%02x]", asem->commands[i]->coding_string[c++]);
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
        if (ft_strequ(commands->command_name, g_op_tab[i].name))
        {
            commands->index = i;
            break ;
        }
        i++;
    }
}

int     get_count_args(t_operation *commands)
{
    int i;

    i = 0;
    while (commands->args[i])
        i++;
    return (i);
}

void    validate_count_args(t_operation *commands)
{
    int count_args;

    count_args = get_count_args(commands);
    if (count_args != g_op_tab[commands->index].count_args)
    {
        ft_printf("***--->[%s]<---***\n", commands->command_name);
        ft_put_error("Invalid count args for instruction");
    }
}

int	is_register(char *str)
{
    if (str == NULL)
        return (0);
    if (str[0] == 'r')
    {
        if (!ft_isdigit(str[1]))
            return (0);
    }
    else if (str[0] != 'r')
        return (0);
    if (!str[2])
        return (1);
    if (!ft_isdigit(str[2]) || str[3])
        return (0);
    return (1);
}

static int	is_dir(char *str)
{
    int i;

    i = 1;
    if (str == NULL)
        return (0);
    if (str[0] == DIRECT_CHAR)
    {
        if (str[i] == '-')
            i++;
        while (str[i])
            if (!ft_isdigit(str[i++]))
                return (0);
    }
    else
        return (0);
    if (str[0] == DIRECT_CHAR && !str[1])
        return (0);
    return (1);
}

static int	is_indir(char *str)
{
    int i;

    i = 0;
    if (str == NULL)
        return (0);
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
    if (str == NULL)
        return (0);
    if (str[i] == DIRECT_CHAR)
        i++;
    if (str[i] == LABEL_CHAR)
    {
        i++;
        while (str[i] && ft_strchr(LABEL_CHARS, str[i]))
            i++;
    }
    else
        return (0);
    if (str[i] != '\0')
        return (0);
    return (1);
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

int    check_reg_comaprison(int type, int arg)
{
    if (type == T_REG)
    {
        if (arg == T_DIR || arg == T_IND || arg == (T_DIR | T_IND))
            return (0);
    }
    return (1);
}

int     check_label_conformity(int type, char *str)
{
    if (type == T_LAB)
    {
        if (str[0] == DIRECT_CHAR)
            type = T_DIR;
        else
            type = T_IND;
    }
    return (type);
}

int     check_indir_conformity(int type, int arg)
{
    if (type == T_IND)
    {
        if (arg== T_DIR || arg == T_REG || arg == (T_DIR | T_REG))
            return (0);
    }
    return (1);
}

int    check_conformity(char *str, int type, t_operation *commands, int i)
{
    int		arg;

    type = check_label_conformity(type, str);
    arg = g_op_tab[commands->index].args[i];
    if (!check_reg_comaprison(type, arg))
        return (0);
    else if (!check_indir_conformity(type, arg))
        return (0);
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
        if (!check_conformity(commands->args[i], type,commands,i))
        {
            ft_printf("***--->[%s]<---***\n", commands->args[i]);
            ft_put_error("Invalid arguments");
        }
        if (type == -1)
        {
            ft_printf("***--->[%s]<---***\n", commands->args[i]);
            ft_put_error("Invalid argument type");
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


void    validate_content(t_asm *asem)
{
    int i;

    i = 0;
    while (asem->commands[i])
    {
        validate_all_content(asem,i);
        if (asem->commands[i]->index  == -1)
        {
            ft_printf("***--->[%s]<---***\n", asem->commands[i]->command_name);
            ft_put_error("Invalid instruction");
        }
        i++;
    }
}

int     get_coding_byte(t_operation *commands)
{
    int i;
    int type;
    char binary[9];
    int k;

    i = 0;
    k = 0;
    while (i < 8)
        binary[i++] = '0';
    binary[i] = '\0';
    i = 0;
    while (commands->args[i])
    {
        type = check_type_arg(commands->args[i]);
        if (type == T_REG || type == T_IND
            || (type == T_LAB && commands->args[i][0] != DIRECT_CHAR))
            binary[k + 1] = '1';
        if (type == T_DIR || type == T_LAB || type == T_IND)
            binary[k] = '1';
        k += 2;
        i++;
    }
    return (ft_atoi_base(binary, 2));
}

static int	get_label_len_between(t_asm *content, int i1, int i2)
{
    int	len;

    len = 0;
    while (i1 < i2)
    {
        len += content->commands[i1]->len;
        i1++;
    }
    return (len);
}

static int	get_label_position(t_asm *content, char *label)
{
    int	i;
    int	j;

    i = 0;
    while (content->commands && content->commands[i])
    {
        j = 0;
        while (content->commands[i]->label && content->commands[i]->label[j])
        {
            if (ft_strequ(content->commands[i]->label[j], label))
                return (i);
            j++;
        }
        i++;
    }
    return (-1);
}

static void	add_op_len(int op_index, t_asm *content)
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

void		asm_get_prog_len(t_asm *content)
{
    int	i;

    i = 0;
    while (content->commands[i])
    {
        content->commands[i]->len = 1;
        if (g_op_tab[content->commands[i]->index].octal_coding)
            content->commands[i]->len++;
        add_op_len(i, content);
        i++;
    }
}

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

void    convert_code(t_operation *commands, t_asm *asem, int a)
{
    int i;
    int type;
    int c;

    i = 0;
    c = 0;
    commands->coding_string[c++] = (unsigned char) g_op_tab[commands->index].opcode;
    if (g_op_tab[commands->index].octal_coding)
        commands->coding_string[c++] = (unsigned char) get_coding_byte(commands);
    while (commands->args[i])
    {
        type = check_type_arg(commands->args[i]);
        if (type == T_REG)
            commands->coding_string[c++] = (unsigned char) ft_atoi(commands->args[i] + 1);
        else if (type == T_IND || (type == T_LAB && asem->commands[a]->args[i][0] != DIRECT_CHAR))
            c = get_indir(asem, a, c, i);
        else if (type == T_DIR || type == T_LAB)
            c = get_t_dir(asem, a,c, i);
        i++;
    }
}

void    generate_hex(t_asm *asem)
{
    int i;

    i = 0;
    asm_get_prog_len(asem);
    while (asem->commands[i])
    {
        convert_code(asem->commands[i], asem, i);
        i++;
    }
}

void    get_magic(t_asm *asem, unsigned int i)
{
    asem->magic[0] = (i >> 24) & 0xFF;
    asem->magic[1] = (i >> 16) & 0xFF;
    asem->magic[2] = (i >> 8) & 0xFF;
    asem->magic[3] = i & 0xFF;
}

void    write_name_to_file(t_asm *asem, int fd)
{
    int i;

    i = (int) ft_strlen(asem->prog_name);
    write(fd, asem->prog_name, (size_t) i);
    while (i < PROG_NAME_LENGTH + 4)
    {
        write(fd, "\0", 1);
        i++;
    }
}

void    write_comment_to_file(t_asm *asem, int fd)
{
    int i;

    i = (int) ft_strlen(asem->comment);
    write(fd, asem->comment, (size_t) i);
    while (i < COMMENT_LENGTH + 4)
    {
        write(fd, "\0", 1);
        i++;
    }
}

void    write_magic_to_file(t_asm *asem, int fd)
{
    int i;

    i = 0;

    while (i < 4)
    {
        write(fd, &asem->magic[i], 1);
        i++;
    }
}

void    write_program_to_file(t_asm *asem, int fd)
{
    int i;

    i = 0;
    while (asem->commands[i])
    {
        write(fd, asem->commands[i]->coding_string, (unsigned)asem->commands[i]->len);
        i++;
    }
}

void    get_prog_size(t_asm *asem)
{
    int i;

    i = 0;
    while (asem->commands[i])
    {
        asem->prog_size += asem->commands[i]->len;
        i++;
    }
}

void    write_bytecode(t_asm *asem, int fd)
{
    write_magic_to_file(asem, fd);
    write_name_to_file(asem, fd);
    get_magic(asem, (unsigned)asem->prog_size);
    write_magic_to_file(asem, fd);
    write_comment_to_file(asem, fd);
    write_program_to_file(asem, fd);
}

void    generate_bytecode(t_asm *asem)
{
    int fd;
    remove(asem->file);
    fd = open(asem->file, O_CREAT | O_WRONLY, 0666);
    if (fd < 0)
        ft_put_error("OOOPS, something went wrong");
    validate_content(asem);
    generate_hex(asem);
    get_magic(asem, COREWAR_EXEC_MAGIC);
    get_prog_size(asem);
    if (!asem->print)
    {
        write_bytecode(asem, fd);
        ft_printf("Writing output program to %s\n", asem->file);
    }
    else
        detailed_print(asem);
}

int     check_filename(const char *str, t_asm *asem)
{
    int i;
    int k;
    char *new_file;
    char *sub_old;

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
    sub_old = ft_strsub(str, 0, (size_t) k);
    new_file = ft_joinfree(sub_old,".cor", FIRST);
    asem->file = new_file;
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
    if (!check_filename(av[ac - 1], asem) || fd < 0)
        error_name(av, ac);
    if (ft_strequ("-a", av[1]))
        asem->print = 1;
    if (!validation(fd, 0, asem))
        ft_put_error("Validation Error");
    generate_bytecode(asem);
    sleep(100);
}