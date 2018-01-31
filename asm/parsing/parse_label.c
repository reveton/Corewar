#include "../asm.h"

static void	add_label_struct(t_operation *op, char *label)
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

size_t    get_label_name(char *s, t_operation *op, size_t i, t_asm *asem)
{
    size_t k;

    i = skip_spaces(s, i);
    k = 0;
    while (ft_strcchr(LABEL_CHARS, s[i + k]))
        k++;
    if (s[i + k] == LABEL_CHAR && k > 0)
    {
        add_label_struct(op, ft_strsub(s, 0, k));
        asem->found_label = 1;
        return (i + k + 1);
    }
    else
    {
        asem->found_label = 2;
        op->command_name = ft_strsub(s, (unsigned int) i, k);
    }
    return (i + k);
}