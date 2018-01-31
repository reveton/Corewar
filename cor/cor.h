#ifndef VIRTUALMACHINE_COR_H
#define VIRTUALMACHINE_COR_H

# include "libft/libft.h"
# include "op.h"
# include <ncurses.h>
# include <fcntl.h>
# include <stdio.h>

/*TEST*/
 typedef struct		s_print
{
	WINDOW			*win_corwar;
	WINDOW			*win_map;
	WINDOW			*win_stat;
	WINDOW			*win;
	WINDOW			*border;
	int				nbr_live;
	int				to_die;
	int				cycle_to_die;
	int				cycle;
	int				status;
}					t_print;
/*TEST*/

typedef struct		s_cursor
{
    int				pln;
    int				cci;
    int				carry;
    int				live;
    char			*bnr_code;
    int				atp[3];
    int				reg[1 + 16];
    int             check;
    t_op			op;
    int				sbk;
    int             opcode_g;
    struct s_cursor	*next;
    int             set_nb;
}					t_cursor;

typedef struct		s_arena
{
    unsigned char	cell;
    int             cursor;
    int             pn;

}					t_arena;

typedef struct		s_champ
{
    int				nb;
    int				nb_set;
    int				start_pos;
    char			*file_name;
    int				last_live;
    unsigned int	magic;
    char			prog_name[PROG_NAME_LENGTH + 1];
    unsigned int	prog_size;
    size_t			full_prog_size;
    char			comment[COMMENT_LENGTH + 1];
    char			*program;
    int				carr_count;
    int             fd;
    unsigned char   magic_bin[4];
    unsigned char   size_bin[4];
}					t_champ;


typedef struct s_cor
{
    int count_players;
    int n;
    int d;
	int p;
    int dump_number;
    t_champ        players[MAX_PLAYERS + 1];
    t_arena        *map;
    t_cursor        *cursor;
    t_print         print;
    int             checks;
    int             cursor_cnt;
    int             win_player;
    int             lev;
    int             ada;
    int             bod;
    int             spd;
	int 			set_pn;
    unsigned int             live;
    unsigned int             add;
    unsigned int             sub;
    unsigned int             aff;
    unsigned int             or;
    unsigned int             xor;
    unsigned int             fork;
    unsigned int             lfork;
    unsigned int             ld;
    unsigned int             ldi;
    unsigned int             lld;
    unsigned int             lldi;
    unsigned int             st;
    unsigned int             sti;
    unsigned int             zjump;
    unsigned int             and;

}              t_cor;

void	init_struct(t_cor **cor);
int     ft_strstr_my(const char *str, const char *to_find, int pos);
void	ft_put_error(char *str);
void parse_arg(char **av, t_cor *cor);
void    parse_magic_number(t_cor *cor, int nb, char *content);
int				convert_chr_to_int(const unsigned char *s);
void    check_magic(t_cor *cor, int nb);
int    parse_prog_name(t_cor *cor, int nb, char *content, int move);
int    parse_prog_size(t_cor *cor, int nb, char *content, int move);
void    check_size(t_cor *cor, int nb);
int    parse_prog_comment(t_cor *cor, int nb, char *content, int move);
void    parse_program(t_cor *cor, int nb, char *content, int move);
void    init_great_war(t_cor *cor, t_cursor *curr_curs);
void    init_cursor(t_cor *cor, int i, t_cursor *next_cursor);
void	get_binary(t_cor *cor, t_cursor *cursor, unsigned link, int cord);
void    validate_commands(t_cursor *cursor, t_cor *cor);
void    exec(t_cor *cor, t_cursor *cursor, unsigned int cd);
void    move_cursor_with_op(t_cursor *cursor, t_cor *cor, int perm);
void    reset_cursor(t_cursor *cursor);
int    ft_fork(t_cursor *cursor, t_cor *cor);
int    lfork(t_cursor *cursor, t_cor *cor, int i, int r);
void    fill_arena(t_cor *cor);
int		ft_dir(t_cor *data, t_cursor *carr, unsigned link, int i);
char			*generate_binary(unsigned char c, t_cor *cor, int curr_i, int z);
int     check_arg(int n, t_cursor *cursor, int levada);
void    error_usage(void);

//Test//
void	nc_print_stat(t_cor *data, WINDOW *win);
void	nc_print_map(t_cor *data, WINDOW *win);
void	change_speed(t_cor *data, int key);
void	get_color(int pn, WINDOW *win);
void	get_carriage_color(int pn, WINDOW *win);
void	nc_refresh(t_cor *data, t_print *print);
void	shut_down_nc(t_cor *data);
void	print_cell(unsigned char cell, WINDOW *win);
void	print_stat_status(t_cor *data, WINDOW *win);
void	print_stat_cycle(t_cor *data, WINDOW *win);
void	print_champs(t_cor *data, WINDOW *win);
void	print_rules(t_cor *data, WINDOW *win);
void	winner_loop(t_cor *data);
void	nc_print_winner(t_cor *data, t_print *p, int winner);
void	nc_start(t_cor *data);
void	nc_pause(t_cor *data);
void	init_colors(void);
void	nc_prepare(t_cor *data, t_print *print);
void	init_ncurses(t_cor *data, t_print *print);
void    corewar(t_cor *cor);

#endif
