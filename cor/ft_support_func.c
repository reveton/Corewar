#include "cor.h"

int     ft_strstr_my(const char *str, const char *to_find, int pos)
{
    size_t i;
    size_t step;
    size_t count;

    i = (size_t) pos;
    step = 0;
    count = 0;
    while (to_find[count])
        count++;
    if (count == 0)
        return (1);
    while (str[i])
    {
        while (to_find[step] == str[i + step])
        {
            if (step == (count - 1))
                return (1);
            step++;
        }
        step = 0;
        i++;
    }
    return (0);
}

void	ft_put_error(char *str)
{
    ft_printf("%s", str);
    exit(0);
}

void    error_usage(void)
{
    ft_printf("Usage: ./corewar <sourcefile.cor>\n");
    ft_printf("Bonuses: \n");
    ft_printf("Set player number [-p [-number]] \n");
    ft_printf("Turn on visualisation [-n] \n");
    ft_printf("Show map on placed cycle [-d [-cycle_number]] \n");
    exit(0);
}
