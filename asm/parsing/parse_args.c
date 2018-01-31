#include "../asm.h"

int     count_arr(char **s)
{
    int i;

    i = 0;
    while (s[i])
        i++;
    return (i);
}

void  parse_arg(char *s, t_operation *commands, size_t i)
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
        commands->count_args++;
        args[k] = ft_strtrim(args[k]);
        free(str);
        k++;
    }
    if (commands->args)
        free(commands->args);
    commands->args = args;
}

