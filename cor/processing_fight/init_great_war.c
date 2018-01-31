#include "../cor.h"

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

void    corewar(t_cor *cor)
{
    int end;

    end = 1;
    if (cor->d == 1 && cor->count_players == 0)
        ft_put_error("Wrong count players");
    else if (cor->d == 1 && cor->dump_number != cor->lev)
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