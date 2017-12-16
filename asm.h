#ifndef ASM_ASM_H
#define ASM_ASM_H
# include "libft/libft.h"
# include "op.h"

typedef struct		s_operation
{
    char			*name;
    char			**args;
    char			**label;
    int				index;
    unsigned char	coding_string[14];
    int				count;
    int				len;
}					t_operation;

typedef struct  s_asm
{
    unsigned int		magic;
    char				*prog_name;
    unsigned int		prog_size;
    char				*comment;
    t_operation         **commands;
}               t_asm;



int     validation(int fd, char *line, t_asm *asem);
void    error_name(char **av, int count_arg);
void	ft_put_error(char *str);
void    error_usage(void);
void	init_struct(t_asm **asem);
void    check_name_comment(char **str, t_asm *asem, int command, char *line);
int	    ft_strposlen(const char *s, int c);
int     count_s(char **s);
size_t	ft_chrpos(const char *s, int c);

#endif
