#include "../asm.h"

static void	add_label_struct(t_operation *commands, char *label)
{
    char	**new_labels;
    int		i;

    i = 0;
    while (commands->label && commands->label[i])
        i++;
    new_labels = (char **)malloc(sizeof(char *) * (i + 2));
    i = 0;
    while (commands->label && commands->label[i])
    {
        new_labels[i] = commands->label[i];
        i++;
    }
    new_labels[i++] = label;
    new_labels[i] = NULL;
    if (commands->label)
        free(commands->label);
    commands->label = new_labels;
}

size_t    get_label_name(char *s, t_operation *commands, size_t i, t_asm *asem)
{
    size_t k;

    i = skip_spaces(s, i);
    k = 0;
    while (ft_strcchr(LABEL_CHARS, s[i + k]))
        k++;
    if (s[i + k] == LABEL_CHAR && k > 0)
    {
        add_label_struct(commands, ft_strsub(s, 0, k));
        asem->found_label = 1;
        return (i + k + 1);
    }
    else
    {
        asem->found_label = 2;
        commands->command_name = ft_strsub(s, (unsigned int) i, k);
    }
    return (i + k);
}