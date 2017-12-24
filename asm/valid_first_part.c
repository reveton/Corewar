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

void    check_name_comment(char *str, t_asm *asem, int command)
{
    int check;
    char **s;

    s = ft_strsplit(str, '"');
    if (s[2] || s[2] != NULL)
    {
        check = check_trash(s[2]);
        if (check == 1)
            ft_put_error("Syntax Error in name or comment");
    }
    if (command == 1 && ft_strlen(s[1]) > PROG_NAME_LENGTH)
        ft_put_error("ERROR(Too large NAME)");
    if (command == 2 && ft_strlen(s[1]) > COMMENT_LENGTH)
        ft_put_error("ERROR(Too large comment)");
    if (command == 1)
        asem->prog_name = ft_strdup(s[1]);
    if (command == 2)
        asem->comment = ft_strdup(s[1]);
    free_str(s);
}