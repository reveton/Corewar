#include "../asm.h"

int	get_label_len_between(t_asm *content, int i1, int i2)
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

int	get_label_position(t_asm *content, char *label)
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
