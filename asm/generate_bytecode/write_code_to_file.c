#include "../asm.h"

void    write_name_to_file(t_asm *asem, int fd)
{
    int i;

    i = (int) ft_strlen(asem->prog_name);
    write(fd, asem->prog_name, (size_t) i);
    while (i < PROG_NAME_LENGTH + 4)
    {
        write(fd, "\0", 1);
        i++;
    }
}

void    write_comment_to_file(t_asm *asem, int fd)
{
    int i;

    i = (int) ft_strlen(asem->comment);
    write(fd, asem->comment, (size_t) i);
    while (i < COMMENT_LENGTH + 4)
    {
        write(fd, "\0", 1);
        i++;
    }
}

void    write_magic_to_file(t_asm *asem, int fd)
{
    int i;

    i = 0;

    while (i < 4)
    {
        write(fd, &asem->magic[i], 1);
        i++;
    }
}

void    write_program_to_file(t_asm *asem, int fd)
{
    int i;

    i = 0;
    while (asem->commands[i] && !asem->commands[i]->check_end)
    {
        write(fd, asem->commands[i]->coding_string, (unsigned)asem->commands[i]->len);
        i++;
    }
}