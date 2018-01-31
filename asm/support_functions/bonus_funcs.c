#include "../asm.h"

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