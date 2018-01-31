#ifndef ASM_ASM_H
#define ASM_ASM_H
# include "libft/libft.h"
# include "op.h"

typedef struct		s_operation
{
    char			*command_name;
    char			**args;
    char			**label;
    int				index;
    unsigned char	coding_string[14];
    int				len;
	unsigned int             count_args;
    int                 check_end;
}					t_operation;

typedef struct  s_asm
{
    char                *file;
    unsigned int		magic[4];
    char				*prog_name;
    unsigned int		prog_size;
    char				*comment;
    t_operation         **commands;
    t_operation         *tmp;
    t_operation         *tmp_ska;
    int                 print;
    int                 com;
    int                 k;
    int                 issetname;
    int                 issetcomment;
    int                 found_label;
    int                 grace;
}               t_asm;



int     validation(int fd, char *line, t_asm *asem);
void    error_name(char **av, int count_arg);
void	ft_put_error(char *str);
void    error_usage(void);
void	init_struct(t_asm **asem);
char    *check_name_comment(char *str, int param, char *tmp, char *tmp2);
int	    ft_strposlen(const char *s, int c);
int    check_type_arg(char *str);
void		get_prog_len(t_asm *content);
void    get_prog_size(t_asm *asem);
void		free_str(char **str);
void    detailed_print(t_asm *asem);
int		ft_strcchr(const char *str, char c);
t_operation     *init_struct_operation(void);
char *remove_comments(char *str);
int find_symbol(char *word, char find);
size_t skip_spaces(char *s, size_t i);
void    find_name_comment(char *line, t_asm* asem, char **str_new);
size_t    get_label_name(char *s, t_operation *commands, size_t i, t_asm *asem);
void  parse_arg(char *s, t_operation *commands, size_t i);
int parse_str(char *s, t_asm *asem);
void    validate_count_args(t_operation *commands);
void    validate_commands(t_operation *commands);
int	is_register(char *str);
int	is_dir(char *str);
int	is_indir(char *str);
int	is_label(char *str);
void    validate_type_args(t_operation *commands);
int    check_conformity(char *str, int type, t_operation *commands, int i);
void    check_exist_label(t_operation *commands, t_asm *asem);
void    validate_content(t_asm *asem);
int     check_filename(const char *str, t_asm *asem);
void    generate_bytecode(t_asm *asem);
void    write_name_to_file(t_asm *asem, int fd);
void    write_comment_to_file(t_asm *asem, int fd);
void    write_magic_to_file(t_asm *asem, int fd);
void    write_program_to_file(t_asm *asem, int fd);
void    get_magic(t_asm *asem, unsigned int i);
void    generate_hex(t_asm *asem);
void    convert_code(t_operation *commands, t_asm *asem, int a);
int    get_indir(t_asm *asem, int i, int v, int a);
int    get_t_dir(t_asm *asem, int i, int v, int a);
int         l_length(t_asm *asem, char *label, int i);
int get_pos(t_asm *asem, char *l, int k, int o);
int distance(t_asm *asem, int start, int index, int length);
int     get_coding_byte(t_operation *commands);
void    check_name_and_comment(t_asm *asem);
int     check_empty_line(char *str);
int check_line(char *line);
int     check_command(char *word);
void    add_to_struct(t_asm *asem, t_operation *op);

int     check_arg(int n, int type);

#endif
