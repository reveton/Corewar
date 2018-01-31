#include "../asm.h"

static int    check_reg_conformity(int type, int arg)
{
    if (type == T_REG)
    {
        if (arg == T_DIR || arg == T_IND || arg == (T_DIR | T_IND))
            return (0);
    }
    return (1);
}

static int     check_label_conformity(int type, char *str)
{
    if (type == T_LAB)
    {
        if (str[0] == DIRECT_CHAR)
            type = T_DIR;
        else
            type = T_IND;
    }
    return (type);
}

static int     check_indir_conformity(int type, int arg)
{
    if (type == T_IND)
    {
        if (arg == T_DIR || arg == T_REG || arg == (T_DIR | T_REG))
            return (0);
    }
    return (1);
}

int    check_conformity(char *str, int type, t_operation *commands, int i)
{
    int		arg;

    type = check_label_conformity(type, str);
    arg = g_op_tab[commands->index].args[i];
    if (!check_reg_conformity(type, arg)
        || !check_indir_conformity(type, arg))
        return (0);
    return (1);
}