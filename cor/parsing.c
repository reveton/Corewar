#include "cor.h"

static void    isset_cor_files(t_cor *cor)
{
    int i;
    int fd;
    off_t size;

    i = 0;
    while (i < cor->count_players)
    {
        if ((fd = open(cor->players[i].file_name, O_RDONLY)) == -1)
            ft_put_error("Can't read source file\n");
        if ((size = lseek(fd, 0, SEEK_END)) < 0)
            ft_put_error("Bad file\n");
        lseek(fd, 0, SEEK_SET);
        cor->players[i].fd = fd;
        cor->players[i].full_prog_size = (size_t) size;
        if (!cor->players[i].nb_set)
            cor->players[i].nb = -(i + 1);
        else
            cor->players[i].nb = cor->players[i].nb_set;
        i++;
    }
}

static void    add_players(char *player, t_cor *cor)
{
    cor->players[cor->count_players].file_name = player;
    cor->count_players++;
    if (cor->count_players > 4)
        ft_put_error("ERROR | Too much players\n");
}

static void fill_and_check_player(t_cor *cor, int nb)
{
    char *content;
    int skip_bytes;

    skip_bytes = 4;
    content = ft_strnew((size_t)cor->players[nb].full_prog_size);
    read(cor->players[nb].fd, content,(size_t)cor->players[nb].full_prog_size);
    parse_magic_number(cor, nb, content);
    check_magic(cor, nb);
    skip_bytes = parse_prog_name(cor, nb, content, skip_bytes) +
            skip_bytes + 4;
    skip_bytes = parse_prog_size(cor, nb, content, skip_bytes) + skip_bytes;
    check_size(cor, nb);
    skip_bytes = parse_prog_comment(cor, nb, content, skip_bytes) + 4 + skip_bytes;
    parse_program(cor, nb, content, skip_bytes);
    free(content);
}

static void parse_cor_files(t_cor *cor)
{
    int i;

    i = 0;
    while (i < cor->count_players)
    {
        fill_and_check_player(cor, i);
        i++;
    }

}

void    check_set_nb(t_cor *cor, char *av)
{
    int i;

    i = 0;
    while (av[i])
    {
        if (av[i] == '-')
            i++;
        if (!ft_isdigit(av[i]))
            ft_put_error("Wrong player number");
        i++;
    }
    cor->players[cor->count_players].nb_set = (int) ft_atoi(av);
}

void parse_arg(char **av, t_cor *cor)
{
    int i;

    i = 0;
    while (av[i])
    {
        if (ft_strequ("-n",av[i]))
            cor->n = 1;
        else if (ft_strequ("-d",av[i]))
        {
            cor->d = 1;
            cor->dump_number = (int) ft_atoi(av[i + 1]);
        }
        if (ft_strequ("-p", av[i]))
            check_set_nb(cor, av[i + 1]);
        if (ft_strstr_my(av[i], ".cor", 0))
            add_players(av[i], cor);
        i++;
    }
    isset_cor_files(cor);
    parse_cor_files(cor);
}