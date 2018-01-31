#include "cor.h"

void	nc_print_stat(t_cor *data, WINDOW *win)
{
    print_stat_status(data, win);
    print_stat_cycle(data, win);
    print_champs(data, win);
    print_rules(data, win);
}

void	nc_print_map(t_cor *data, WINDOW *win)
{
    int i;
    int x;
    int y;

    i = -1;
    x = 1;
    y = 3;
    wmove(win, 3, 3);
    while (++i < MEM_SIZE)
    {
        if (data->map[i].cursor == 1)
            get_carriage_color(data->map[i].pn, win);
        else
            get_color(data->map[i].pn, win);
        print_cell(data->map[i].cell, win);
        if (x >= 64)
        {
            x = 0;
            y++;
            wmove(win, y, 3);
        }
        x++;
    }
}

void	change_speed(t_cor *data, int key)
{
    if (key == 'w')
        if (data->spd > 1)
            data->spd--;
    if (key == 'q')
        if (data->spd > 11)
            data->spd -= 10;
    if (key == 'e')
        data->spd++;
    if (key == 'r')
        data->spd += 10;
}

void	get_color(int pn, WINDOW *win)
{
    if (pn == 0)
        wattron(win, COLOR_PAIR(5));
    else if (pn == 1 || pn == -1)
        wattron(win, COLOR_PAIR(1));
    else if (pn == 2 || pn == -2)
        wattron(win, COLOR_PAIR(2));
    else if (pn == 3 || pn == -3)
        wattron(win, COLOR_PAIR(3));
    else if (pn == 4 || pn == -4)
        wattron(win, COLOR_PAIR(4));
}

void	get_carriage_color(int pn, WINDOW *win)
{
    if (pn == 0)
        wattron(win, COLOR_PAIR(10));
    else if (pn == 1)
        wattron(win, COLOR_PAIR(6));
    else if (pn == 2)
        wattron(win, COLOR_PAIR(7));
    else if (pn == 3)
        wattron(win, COLOR_PAIR(8));
    else if (pn == 4)
        wattron(win, COLOR_PAIR(9));
}

void	nc_refresh(t_cor *data, t_print *print)
{
    nc_print_map(data, print->win_map);
    nc_print_stat(data, print->win_stat);
    wrefresh(print->win_map);
    wrefresh(print->win_stat);
}

void	shut_down_nc(t_cor *data)
{
    delwin(data->print.win_corwar);
    delwin(data->print.win_map);
    delwin(data->print.win_stat);
    endwin();
    exit(1);
}


void	print_cell(unsigned char cell, WINDOW *win)
{
    wprintw(win, "%02x", cell);
    wattron(win, COLOR_PAIR(5));
    wprintw(win, " ");
}

void	print_stat_status(t_cor *data, WINDOW *win)
{
    char *status;

    if (data->print.status == 0)
        status = "PAUSED";
    else
        status = "RUNNING";
    wmove(win, 6, 50 - ((ft_strlen(status) + 7) / 2));
    if (data->print.status == 0)
    {
        wprintw(win, "Status : ", status);
        wattron(win, COLOR_PAIR(3));
    }
    else
    {
        wprintw(win, " Status : ", status);
        wattron(win, COLOR_PAIR(1));
    }
    wprintw(win, "%s ", status);
    wattroff(win, COLOR_PAIR(5));
    wmove(win, 8, 50 - ((ft_strlen("Game Speed :  ") + 6) / 2));
    wprintw(win, "Game Speed : %i ", data->spd);
}

void	print_stat_cycle(t_cor *data, WINDOW *win)
{
    wmove(win, 12, 50 - (ft_strlen("Info") / 2));
    wprintw(win, " Info");
    wmove(win, 14, 50 - (ft_strlen("Cycle :    ") / 2));
    wprintw(win, "Cycle : %i", data->print.cycle);
}

void	print_champs(t_cor *data, WINDOW *win)
{
    int n;
    int width;
    int height;

    height = 24;
    wmove(win, height - 2, 50 - (int)ft_strlen("Players") / 2);
    wprintw(win, " Players");
    n = -1;
    while (++n < data->count_players)
    {
        width = 50 - ((int)ft_strlen(data->players[n].prog_name) / 2);
        wmove(win, height, width);
        get_color(data->players[n].nb_set, win);
        wprintw(win, "%s", data->players[n].prog_name);
        wattroff(win, COLOR_PAIR(5));
        height += 2;
    }
}

void	print_rules(t_cor *data, WINDOW *win)
{
    wmove(win, 35, 50 - ft_strlen("Rules") / 2);
    wprintw(win, " Rules");
    wmove(win, 37, 50 - (ft_strlen("Cycle To Die") / 2) - 6);
    wprintw(win, "Cycle To Die : %i    ", data->print.cycle_to_die);
    wmove(win, 39, 50 - (ft_strlen("Cycle Delta") / 2) - 6);
    wprintw(win, "Cycle Delta : %i", CYCLE_DELTA);
    wmove(win, 41, 50 - (ft_strlen("Nbr Live") / 2) - 4);
    wprintw(win, "Nbr Live : %i", NBR_LIVE);
    wmove(win, 43, 50 - (ft_strlen("Max Checks") / 2) - 5);
    wprintw(win, "Max Checks : %i", MAX_CHECKS);
}


void	winner_loop(t_cor *data)
{
    int quit;
    int key;

    quit = 'o';
    while (quit != 'x')
    {
        key = getch();
        if (key == 'x')
            quit = key;
    }
    shut_down_nc(data);
}

void	nc_print_winner(t_cor *data, t_print *p, int winner)
{
    int		prms[4];
    char	*name;

    name = data->players[winner].prog_name;
    prms[0] = 20 + ((int)ft_strlen(name));
    prms[1] = 5;
    prms[2] = (COLS - prms[0]) / 2;
    prms[3] = (LINES - prms[1]) / 2;
    p->border = newwin(prms[1] + 2, prms[0] + 2, prms[3] - 1, prms[2] - 1);
    p->win = newwin(prms[1], prms[0], prms[3], prms[2]);
    box(p->border, 0, 0);
    wmove(p->win, 2, (prms[0] - ((int)ft_strlen(name) + 10)) / 2);
    wprintw(p->win, "Winner is ");
    get_color(winner + 1, p->win);
    wprintw(p->win, "%s", name);
    refresh();
    wrefresh(p->border);
    wrefresh(p->win);
    winner_loop(data);
}

void	nc_start(t_cor *data)
{
    int quit;
    int key;

    quit = 'o';
    while (quit != 'x')
    {
        if (data->print.status == 0)
            data->print.status = 1;
        timeout(data->spd);
        key = getch();
        if (key == 'x')
            quit = key;
        else if (key == ' ')
            nc_pause(data);
        else if (key == 'q' || key == 'w' || key == 'e' || key == 'r')
            change_speed(data, key);
        init_great_war(data, data->cursor);
        nc_refresh(data, &data->print);
    }
    shut_down_nc(data);
}

void	nc_pause(t_cor *data)
{
    int key;

    if (data->print.status == 1)
    {
        data->print.status = 0;
        nc_print_stat(data, data->print.win_stat);
        wrefresh(data->print.win_stat);
    }
    key = getch();
    if (key == 'x')
        shut_down_nc(data);
    else if (key == ' ')
        nc_start(data);
    else if (key == 'q' || key == 'w' || key == 'e' || key == 'r')
    {
        change_speed(data, key);
        nc_refresh(data, &data->print);
        nc_pause(data);
    }
    else
        nc_pause(data);
}

void	init_colors(void)
{
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_CYAN, COLOR_BLACK);
    init_pair(5, COLOR_WHITE, COLOR_BLACK);
    init_pair(6, COLOR_BLACK, COLOR_GREEN);
    init_pair(7, COLOR_BLACK, COLOR_BLUE);
    init_pair(8, COLOR_BLACK, COLOR_RED);
    init_pair(9, COLOR_BLACK, COLOR_CYAN);
    init_pair(10, COLOR_BLACK, COLOR_WHITE);
}

void	nc_prepare(t_cor *data, t_print *print)
{
    int os_x;
    int os_y;
    int height;
    int width;

    width = 300;
    height = 76;
    os_x = (COLS - width) / 2;
    os_y = (LINES - height) / 2;
    print->win_corwar = newwin(height, width, os_y, os_x);
    print->win_map = newwin(height - 8, width - 50, os_y + 3, os_x + 2);
    print->win_stat = newwin(height - 4, 100, os_y + 2, os_x + 198);
    box(print->win_corwar, 0, 0);
    nc_print_map(data, print->win_map);
    nc_print_stat(data, print->win_stat);
    refresh();
    wrefresh(print->win_corwar);
    wrefresh(print->win_map);
    wrefresh(print->win_stat);
}

void	init_ncurses(t_cor *data, t_print *print)
{
    char *title;
    char *help;

    title = "CoreWar v. 1.1";
    help = "Press 'space' to start/pause. Press 'x' to quit.";
    initscr();
    noecho();
    curs_set(FALSE);
    cbreak();
    start_color();
    init_colors();
    move(3, (COLS - (int)ft_strlen(title)) / 2);
    printw("%s", title);
    move(4, (COLS - (int)ft_strlen(help)) / 2);
    printw("%s", help);
    refresh();
    nc_prepare(data, print);
    nc_pause(data);
}
