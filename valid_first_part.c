#include "asm.h"

int	ft_strposlen(const char *s, int c)
{
    size_t	i;
    int k;

    i = 0;
    k = 0;
    if (!s || s[0] == '\0')
        return (0);
    while (s[i])
    {
        if (s[i] == (char)c)
            k++;
        i++;
    }
    return (k);
}

size_t	ft_chrpos(const char *s, int c)
{
    size_t	i;
    size_t  k;

    i = 0;
    k = 0;
    if (!s || s[0] == '\0')
        return (0);
    while (s[i])
    {
        if (s[i] == (char)c)
            k = i;
        i++;
    }
    return (k);
}

int     check_trash(char *str)
{
    int check;
    int i;

    check = 0;
    i = 0;
    while (str[i])
    {
        if (ft_isalpha(str[i]))
            check = 1;
        i++;
    }
    return (check);
}

void    check_name_comment(char **str, t_asm *asem, int command, char *line)
{
    int check;

    if (str[2])
    {
        check = check_trash(str[2]);
        if (check == 1)
            ft_put_error("Syntax Error in name or comment");
    }
    if (ft_strposlen(line, '\"') > 2)
        ft_put_error("ERROR(Too much quotes)");
    if (command == 1 && ft_strlen(str[1]) > PROG_NAME_LENGTH)
        ft_put_error("ERROR(Too large NAME)");
    if (command == 2 && ft_strlen(str[1]) > COMMENT_LENGTH)
        ft_put_error("ERROR(Too large comment)");
    if (command == 1)
        asem->prog_name = str[1];
    if (command == 2)
        asem->comment = str[1];
}