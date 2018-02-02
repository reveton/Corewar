#include "../cor.h"

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