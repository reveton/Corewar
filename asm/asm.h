#ifndef ASM_ASM_H
#define ASM_ASM_H
#define LEAK system("leaks $(ps | grep corewar | grep ttys000 | cut -d ' ' -f 1)")
# include "libft/libft.h"
# include "op.h"

typedef enum	e_del
{
    FIRST,
    SECOND,
    BOTH
}				t_del;

typedef struct		s_operation
{
    char			*command_name;
    char			**args;
    char			**label;
    int				index;
    unsigned char	coding_string[14];
    int				len;
    int             count_args;
}					t_operation;

typedef struct  s_asm
{
    char                *file;
    unsigned int		magic[4];
    char				*prog_name;
    unsigned int		prog_size;
    char				*comment;
    t_operation         **commands;
    int                 print;
}               t_asm;



int     validation(int fd, char *line, t_asm *asem);
void    error_name(char **av, int count_arg);
void	ft_put_error(char *str);
void    error_usage(void);
void	init_struct(t_asm **asem);
void    check_name_comment(char *str, t_asm *asem, int command);
int	    ft_strposlen(const char *s, int c);
int    check_type_arg(char *str);
void		asm_get_prog_len(t_asm *content);
void    get_prog_size(t_asm *asem);
char		*ft_joinfree(char *str1, char *str2, t_del string);
void		free_str(char **str);



/*
 *
 1 - 256 -1
 unsigned char  (0 - 255)

 coding_string[0] = 11;

 sti         r15    %0   r14

[11][100][15][0][0][14]




 unsigned char byte;

 01 10 01 00 -

 01100100



 000000000
 111111111



















 1+2+1 = 4

 char *arg;
 []



 */

#endif
