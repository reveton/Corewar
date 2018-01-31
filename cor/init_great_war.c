#include "cor.h"

void    move_cursor_with_op(t_cursor *cursor, t_cor *cor, int perm)
{
    perm = cursor->cci;
    cor->map[perm].cursor = cor->lev;
    perm = perm + cursor->sbk;
    if (cor->lev < perm)
        perm = (perm % MEM_SIZE);
    if (cor->lev > perm)
        perm = (MEM_SIZE + (perm % MEM_SIZE));
    cor->map[perm].cursor = cor->ada;
    cursor->cci = perm;
}

void    get_op_struct(t_cor *cor, t_cursor *cursor, int i)
{
    if (g_op_tab[i].opcode == (unsigned int) cor->map[cursor->cci].cell)
    {
        cursor->op.opcode = g_op_tab[i].opcode;
        cursor->op.label_size = g_op_tab[i].label_size;
        cursor->op.name = g_op_tab[i].name;
        cursor->opcode_g = i;
        cursor->op.count_args = g_op_tab[i].count_args;
        if (g_op_tab[i].opcode == cursor->op.opcode)
        {
            cursor->op.cycles = g_op_tab[i].cycles - 1;
            if ((int) cursor->op.cycles < 0)
                cursor->op.cycles = 0;
        }
    }
    if (++i < OP_COUNT - 2)
        get_op_struct(cor, cursor, i);
}

void    reset_cursor(t_cursor *cursor)
{
    int i;

    i = -1;
    cursor->bnr_code = NULL;
    cursor->sbk = 0;
    cursor->check = FALSE;
    cursor->opcode_g = -1;
    while (++i < 3)
    {
        cursor->atp[i] = 0;
        cursor->op.args[i] = 0;
    }
    cursor->op.name = NULL;
    cursor->op.count_args = 0;
    cursor->op.opcode = 0;
    cursor->op.cycles = 0;
    cursor->op.octal_coding = 0;
    cursor->op.label_size = 0;
}

void	gto(t_cor *cor, t_cursor *cursor, int i)
{
    int cord;

    cursor->sbk += cor->ada;
    if (!g_op_tab[i].octal_coding)
    {
        if (g_op_tab[i].octal_coding == (unsigned int)cor->lev)
            cursor->op.args[0] = ft_dir(cor, cursor, g_op_tab[i].label_size, 0);
    }
    else
    {
        cord = (cursor->sbk + cursor->cci);
        cursor->bnr_code = generate_binary(cor->map[cord].cell,
                                           cor, (6 + cor->ada), cor->lev);
        cursor->sbk++;
        get_binary(cor, cursor, g_op_tab[i].label_size, cor->lev);
        free(cursor->bnr_code);
    }
    if (g_op_tab[i].opcode == cursor->op.opcode)
        validate_commands(cursor, cor);
}

int    exec_function(t_cursor *cursor, t_cor *cor, unsigned int cd)
{
        if (cd == cor->fork || cd == cor->lfork)
        {
            move_cursor_with_op(cursor, cor, cor->lev);
            if (cd == cor->fork && cursor->check == cor->ada)
                return (ft_fork(cursor, cor));
            else
                return (lfork(cursor, cor, 0 ,0));
        }
        else if (cursor->check == cor->ada)
            exec(cor, cursor, cd);
        move_cursor_with_op(cursor, cor, cor->lev);
    return (cor->lev);
}

void    check_current_cursor(t_cor *cor, t_cursor *cursor)
{
    if (cursor->op.cycles)
    {
        cursor->op.cycles -= cor->ada;
        if (!cursor->op.cycles)
        {
            if (cursor->op.opcode)
                gto(cor, cursor, cursor->opcode_g);
            exec_function(cursor, cor, cursor->op.opcode);
        }
    }
    else
    {
        reset_cursor(cursor);
        get_op_struct(cor, cursor, cor->lev);
        if (!cursor->op.cycles)
        {
            cor->map[cursor->cci].cursor = cor->lev;
            if (cor->lev > cursor->cci)
                cursor->cci = (MEM_SIZE - cor->ada) - cursor->cci;
            if ((MEM_SIZE - cor->ada) <= cursor->cci)
                cursor->cci = (cor->ada * -1);
            cursor->cci += cor->ada;
            cor->map[cursor->cci].cursor = cor->ada;
        }
    }
}

void    cursor_kaput(t_cor *cor, t_cursor *old, t_cursor *temp)
{
    t_cursor *now;

    if (!cor->cursor || !old)
        return ;
    now = cor->cursor->next;
    old->live = cor->lev;
    while (now)
    {
        if (!now->live)
        {
            temp = now;
            old->next = now->next;
            now = old;
            free(temp);
        }
        old = now;
        now->live = cor->lev;
        now = now->next;
    }
}

void print_map(t_cor *cor)
{
    int i;
    int x;

    i = 0;
    x = 0;
    while (i < MEM_SIZE)
    {
        x++;
        ft_printf("%02x ", cor->map[i].cell);
        if (x >= 64)
        {
            x = 0;
            ft_printf("\n");
        }
        i++;
    }
}

void    dump_corewar(t_cor *cor)
{
    int i;

    i = 0;
    while (i < cor->dump_number)
    {
        init_great_war(cor, cor->cursor);
        i++;
    }
    print_map(cor);
}

void    corewar(t_cor *cor)
{
    int end;

    end = 1;
    if (cor->d == 1 && cor->dump_number != cor->lev)
        dump_corewar(cor);
    else if (cor->d == 1 && cor->dump_number == cor->lev)
        ft_put_error("Wrong dump number");
    else
    {
        while (end)
            init_great_war(cor, cor->cursor);
    }
}

int		count_cursors(t_cor *data, int i)
{
    t_cursor	*nowt;

    nowt = data->cursor;
    while (nowt)
    {
        nowt = nowt->next;
        i++;
    }
    return (i);
}

void    print_winner(t_cor *cor)
{
    if (cor->n == 1)
        nc_print_winner(cor, &cor->print, cor->win_player);
    else
    {
        ft_printf("Congratulations!!!\n");
        ft_printf("Player: ");
        ft_printf("%d", cor->players[cor->win_player].nb);
        ft_printf(" (%s)", cor->players[cor->win_player].prog_name);
        ft_printf(" won\n");
        exit(0);
    }
}

void    decrease_cycles(t_cor *cor)
{
    if (cor->print.nbr_live < NBR_LIVE)
    {
        if (cor->checks > MAX_CHECKS)
        {
            if (cor->lev < (cor->print.cycle_to_die - CYCLE_DELTA))
                cor->print.cycle_to_die -= CYCLE_DELTA;
            else
                cor->print.cycle_to_die = cor->ada;
            cor->checks = cor->lev;
        }
    }
    else
    {
        if (cor->lev < (cor->print.cycle_to_die - CYCLE_DELTA))
            cor->print.cycle_to_die -= CYCLE_DELTA;
        else
            cor->print.cycle_to_die = cor->ada;
        cor->checks = cor->lev;
    }
    cor->print.nbr_live = cor->lev;
    cor->print.to_die = cor->print.cycle_to_die;
}

void    init_great_war(t_cor *cor, t_cursor *curr_curs)
{
    t_cursor *temp;

    while (curr_curs)
    {
        check_current_cursor(cor, curr_curs);
        curr_curs = curr_curs->next;
    }
    if (!cor->print.to_die)
    {
        cor->checks += cor->ada;
        while (cor->cursor && !cor->cursor->live)
        {
            temp = cor->cursor;
            cor->cursor = cor->cursor->next;
            free(temp);
        }
        cursor_kaput(cor, cor->cursor, 0);
        decrease_cycles(cor);
        if (!count_cursors(cor, cor->lev))
            print_winner(cor);
    }
    cor->print.cycle += cor->ada;
    cor->print.to_die -= cor->ada;
}