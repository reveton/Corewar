#include "cor.h"

void    validate_live_zjump_fork_lfork(t_cursor *cursor)
{
    if (cursor->atp[0] != T_DIR)
        ft_put_error("Error | Wrong argument type");
    if (cursor->op.count_args != 1)
        ft_put_error("Error | Wrong args count");
    cursor->check = 1;
}

void    validate_ld(t_cursor *cursor)
{
    if (cursor->op.count_args == 2)
    {
        if (check_arg(1, cursor, 1))
        {
            if (check_arg(3, cursor, 0) || check_arg(2, cursor, 0))
            {
                cursor->check = 1;
                return ;
            }
        }
    }
    return ;
}

void    validate_st(t_cursor *cursor)
{
    if (cursor->op.count_args == 2)
    {
        if (check_arg(1, cursor, 0))
        {
            if (check_arg(3, cursor, 0) || check_arg(1, cursor, 0))
            {
                cursor->check = 1;
                return ;
            }
        }
    }
}

void    validate_add(t_cursor *cursor)
{
    if (cursor->op.count_args == 3)
    {
        if (check_arg(1, cursor, 0))
        {
            if (check_arg(1, cursor, 1) && check_arg(1, cursor, 2))
            {
                cursor->check = 1;
                return ;
            }
        }
    }
}

void    validate_sub(t_cursor *cursor)
{
    if (cursor->op.count_args == 3)
    {
        if (check_arg(1, cursor, 0))
        {
            if (check_arg(1, cursor, 1) && check_arg(1, cursor, 2))
            {
                cursor->check = 1;
                return ;
            }
        }
    }
}

void    validate_and_or_xor(t_cursor *cursor)
{
    if (cursor->op.count_args == 3)
    {
        if (check_arg(1, cursor, 0)
            || check_arg(2, cursor, 0)
            || check_arg(3, cursor, 0))
        {
            if (check_arg(1, cursor, 1)
                || check_arg(2, cursor, 1)
                || check_arg(3, cursor, 1))
            {
                if (check_arg(1, cursor, 2)
                    || check_arg(2, cursor, 2))
                {
                    cursor->check = 1;
                    return ;
                }
            }
        }
    }
}

void    validate_ldi_lldi(t_cursor *cursor)
{
    if (cursor->op.count_args == 3)
    {
        if (check_arg(1, cursor, 0)
            || check_arg(2, cursor, 0)
            || check_arg(3, cursor, 0))
        {
            if (check_arg(1, cursor, 1)
                || check_arg(2, cursor, 1))
            {
                if (check_arg(1, cursor, 2))
                {
                    cursor->check = 1;
                    return ;
                }
            }
        }
    }
}

void    validate_sti(t_cursor *cursor)
{
    if (cursor->op.count_args == 3)
    {
        if (check_arg(1, cursor, 0))
        {
            if (check_arg(1, cursor, 1)
                || check_arg(2, cursor, 1)
                || check_arg(3, cursor, 1))
            {
                if (check_arg(1, cursor, 2)
                    || check_arg(2, cursor, 2))
                {
                    cursor->check = 1;
                    return ;
                }
            }
        }
    }
}

void    validate_lld(t_cursor *cursor)
{
    if (cursor->op.count_args == 2)
    {
        if (check_arg(1, cursor, 0)
            || check_arg(2, cursor, 0))
        {
            if (check_arg(1, cursor, 1))
            {
                cursor->check = 1;
                return;
            }
        }

    }
}

void    validate_aff(t_cursor *cursor)
{
    if (cursor->op.count_args == 1)
    {
        if (check_arg(1, cursor, 0))
        {
            cursor->check = 1;
            return ;
        }
    }
}

void    validate_commands(t_cursor *cursor, t_cor *cor)
{
    if (cursor->op.opcode == cor->live
        || cursor->op.opcode == cor->zjump
        || cursor->op.opcode == cor->fork
        || cursor->op.opcode == cor->lfork)
        validate_live_zjump_fork_lfork(cursor);
    if (cursor->op.opcode == cor->ld)
        validate_ld(cursor);
    if (cursor->op.opcode == cor->st)
        validate_st(cursor);
    if (cursor->op.opcode == cor->add)
        validate_add(cursor);
    if (cursor->op.opcode == cor->sub)
        validate_sub(cursor);
    if (cursor->op.opcode == cor->and
        || cursor->op.opcode == cor->or
        || cursor->op.opcode == cor->xor)
        validate_and_or_xor(cursor);
    if (cursor->op.opcode == cor->ldi
        || cursor->op.opcode == cor->lldi)
        validate_ldi_lldi(cursor);
    if (cursor->op.opcode == cor->sti)
        validate_sti(cursor);
    if (cursor->op.opcode == cor->lld)
        validate_lld(cursor);
    if (cursor->op.opcode == cor->aff)
        validate_aff(cursor);
}
