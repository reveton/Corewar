#include "../asm.h"

void    convert_code(t_operation *commands, t_asm *asem, int a)
{
    int i;
    int type;
    int c;

    i = 0;
    c = 0;
    commands->coding_string[c++] = (unsigned char) g_op_tab[commands->index].opcode;
    if (g_op_tab[commands->index].octal_coding)
        commands->coding_string[c++] = (unsigned char) get_coding_byte(commands);
    while (commands->args[i])
    {
        type = check_type_arg(commands->args[i]);
        if (type == T_REG)
            commands->coding_string[c++] = (unsigned char) ft_atoi(commands->args[i] + 1);
        else if (type == T_IND || (type == T_LAB && asem->commands[a]->args[i][0] != DIRECT_CHAR))
            c = get_indir(asem, a, c, i);
        else if (type == T_DIR || type == T_LAB)
            c = get_t_dir(asem, a,c, i);
        i++;
    }
}

void    generate_hex(t_asm *asem)
{
    int i;

    i = 0;
    get_prog_len(asem);
    while (asem->commands[i] && !asem->commands[i]->check_end)
    {
        convert_code(asem->commands[i], asem, i);
        i++;
    }
}

void    write_bytecode(t_asm *asem, int fd)
{
    write_magic_to_file(asem, fd);
    write_name_to_file(asem, fd);
    get_magic(asem, (unsigned)asem->prog_size);
    write_magic_to_file(asem, fd);
    write_comment_to_file(asem, fd);
    write_program_to_file(asem, fd);
}



void    generate_bytecode(t_asm *asem)
{
    int fd;
    remove(asem->file);
    fd = open(asem->file, O_CREAT | O_WRONLY, 0666);
    if (fd < 0)
        ft_put_error("OOOPS, something went wrong");
    validate_content(asem);
    generate_hex(asem);
    get_magic(asem, COREWAR_EXEC_MAGIC);
    get_prog_size(asem);
    if (!asem->print)
    {
        write_bytecode(asem, fd);
        ft_printf("Writing output program to %s\n", asem->file);
    }
    else
        detailed_print(asem);
}