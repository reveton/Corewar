#include "asm.h"

void	ft_put_error(char *str)
{
    ft_printf("%s", str);
    exit(0);
}

void    error_name(char **av, int count_arg)
{
    ft_printf("Can't read source file %s", av[count_arg - 1]);
    exit(0);
}

void    error_usage(void)
{
    ft_printf("Usage: ./asm <sourcefile.s>");
    exit(0);
}