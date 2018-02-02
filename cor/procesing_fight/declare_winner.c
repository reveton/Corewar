#include "../cor.h"

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
//    if (cor->n == 1)
//        nc_print_winner(cor, &cor->print, cor->win_player);
//    else
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

