#include "../asm.h"

int     get_coding_byte(t_operation *commands)
{
    int i;
    int type;
    char binary[9];
    int k;

    i = 0;
    k = 0;
    while (i < 8)
        binary[i++] = '0';
    binary[i] = '\0';
    i = 0;
    while (commands->args[i])
    {
        type = check_type_arg(commands->args[i]);
        if (type == T_REG || type == T_IND
            || (type == T_LAB && commands->args[i][0] != DIRECT_CHAR))
            binary[k + 1] = '1';
        if (type == T_DIR || type == T_LAB || type == T_IND)
            binary[k] = '1';
        k += 2;
        i++;
    }
    return (ft_atoi_base(binary, 2));
}

