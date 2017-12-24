#include "asm.h"

char *remove_comments(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == COMMENT_CHAR)
        {
            str[i] = '\0';
            break;
        }
        i++;
    }
    return (str);
}

size_t skip_spaces(char *s, size_t i)
{
    while (s[i] == ' ' || s[i] == '\t' || s[i] == '\v'
           || s[i] == '\f' || s[i] == '\r')
        i++;
    return (i);
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
    return (commands);
}



int find_symbol(char *word, char find)
{
    if (ft_strposlen(word, find) > 0)
        return (1);
    return (0);
}

int		ft_strcchr(const char *str, char c)
{
    size_t i;

    i = 0;
    while (str[i])
    {
        if (str[i] == c)
            return (1);
        i++;
    }
    return (0);
}

void	asm_add_label(t_operation *op, char *label)
{
    char	**new_labels;
    int		i;

    i = 0;
    while (op->label && op->label[i])
        i++;
    new_labels = (char **)malloc(sizeof(char *) * (i + 2));
    i = 0;
    while (op->label && op->label[i])
    {
        new_labels[i] = op->label[i];
        i++;
    }
    new_labels[i++] = label;
    new_labels[i] = NULL;
    if (op->label)
        free(op->label);
    op->label = new_labels;
}

size_t    parse_label_name(char *s, t_operation *op, size_t i)
{
    size_t k;

    i = skip_spaces(s, i);
    k = 0;
    while (ft_strcchr(LABEL_CHARS, s[i + k]))
        k++;
    if (s[i + k] == LABEL_CHAR && k > 0)
    {
        asm_add_label(op, ft_strsub(s, 0, k));
        return (i + k + 1);
    }
    else
        op->command_name = ft_strsub(s, (unsigned int) i, k);
    return (i + k);
}

void  parse_arg(char *s, t_operation *op, size_t i)
{
    size_t tmp;
    char *str;
    char **args;
    size_t k;

    tmp = i;
    k = 0;
    while (s[i])
        i++;
    str = ft_strsub(s, (unsigned int) tmp, i);
    args = ft_strsplit(str, SEPARATOR_CHAR);
    free(str);
    while (args[k])
    {
        str = args[k];
        op->count_args++;
        args[k] = ft_strtrim(args[k]);
        free(str);
        k++;
    }
    op->args = args;
}

void    add_to_struct(t_asm *asem, t_operation *op)
{
    int			i;
    t_operation	**new_commands;

    i = 0;
    while (asem->commands && asem->commands[i])
        i++;
    new_commands = (t_operation	**)malloc(sizeof(t_operation *) * (i + 2));
    i = 0;
    while (asem->commands && asem->commands[i])
    {
        new_commands[i] = asem->commands[i];
        i++;
    }
    new_commands[i++] = op;
    new_commands[i] = NULL;
    if (asem->commands)
        free(asem->commands);
    asem->commands = new_commands;
}

int parse_str(char *s, t_asm *asem)
{
    t_operation *op;
    size_t i;

    i = 0;
    op = init_struct_operation();

    while (op->command_name == NULL)
        i = parse_label_name(s, op, i);
    parse_arg(s, op ,i);
    add_to_struct(asem,op);
    return (0);
}


char    *convert_str(char *str)
{
    int i;
    int k;
    int count;
    char *new_str;

    i = 0;
    k = 0;
    count = (int) ft_strlen(str);
    new_str = malloc(sizeof(char) * count + 1);
    while (str[i])
    {
        if (str[i] == ' ' || str[i] == '\t')
            i++;
        else
        {
            new_str[k] = str[i];
            i++;
            k++;
        }
        if (str[i] == '\"')
            break;
    }
    new_str[k] = '\0';
    return (new_str);
}

int     check_command(char *word)
{
    char **s;
    char *str;

    if (word[0] == '\0')
        return (0);
    str = convert_str(word);
    s = ft_strsplit(str, '\"');
    free(str);
    if (find_symbol(word, '\"'))
    {
        if (ft_strequ(s[0], NAME_CMD_STRING))
        {
            free_str(s);
            return (1);
        }
        else if (ft_strequ(s[0], COMMENT_CMD_STRING))
        {
            free_str(s);
            return (2);
        }
        else
            ft_put_error("Syntax error in name or comment");
    }
    free_str(s);
    return (3); //Labels and commands
}

int check_line(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (ft_isalpha(line[i]))
            return (1);
        i++;
    }
    return (0);
}

int     check_empty_str(const char *line)
{
    int i;
    int check;
    int quote;

    i = 0;
    quote = 0;
    check = 0;
    if (line == NULL)
        return (0);

    while (line[i])
    {
        if (line[i] == '"' && line[i + 1] == '"')
            check = 1;
        if (line[i] == '"')
            quote++;
        i++;
    }
    if (quote > 2)
        ft_put_error("ERROR(quotes)");
    if (check == 1)
        return (1);
    return (0);
}

void    fill_empty_struct(t_asm *asem, int command)
{
    if (command == 1)
        asem->prog_name = NULL;
    else if (command == 2)
        asem->comment = NULL;
}

char    *check_quotes(int fd, char *str, char *line)
{
    char *str_new;
    char *s1;

    str_new = ft_strdup(str);
    s1 = 0;
    while (get_next_line(fd, &line) && line)
    {
        s1 = ft_strjoin(str_new, line);
        if (!find_symbol(line,'"'))
            s1 = ft_joinfree(s1, "\n", FIRST);
        if (line[0] != '\n' && line[1] != '\n')
            free(line);
        if (find_symbol(line, '"'))
            break;
    }
    return (s1);
}

int validation(int fd, char *line, t_asm *asem)
{
    char *str;
    char *str_new;
    int command;

    while (get_next_line(fd, &line) && line)
    {
        str = remove_comments(line);
        command = check_command(str);
        if (command == 0 || !check_line(line))
            ;
        else if (command == 1 || command == 2)
        {
            str_new = line;
            if (ft_strposlen(line, '"') != 2)
                str_new = check_quotes(fd, line, 0);
            if (!check_empty_str(str_new))
                check_name_comment(str_new, asem, command);
            else
                fill_empty_struct(asem, command);
        }
        else if (command == 3)
            parse_str(line,asem);
        if (line[0] != '\n' && line[1] != '\n')
            free(line);
    }
    return (1);
}