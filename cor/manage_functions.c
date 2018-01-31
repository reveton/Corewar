#include "cor.h"

int     check_arg(int n, t_cursor *cursor, int levada)
{
    if (n == 1 && (cursor->atp[levada] == T_REG))
        return (1);
    if (n == 2 && (cursor->atp[levada] == T_DIR))
        return (1);
    if (n == 3 && (cursor->atp[levada] == T_IND))
        return (1);
    return (0);
}

int				convert_uns_int(unsigned n)
{
    return ((int16_t)n);
}

unsigned char	*convert_int_to_str(int nbr)
{
    unsigned char *s;
    int i;
    int byte;

    i = -1;
    byte = 24;
    s = (unsigned char *)malloc(sizeof(char) * 4);
    while (++i < 4)
    {
        s[i] = (unsigned char)((nbr >> byte) & 0xFF);
        byte -= 8;
    }
    return (s);
}

int				convert_chr_to_int(const unsigned char *s)
{
    int nbr;
    int i;
    int byte;

    i = 0;
    byte = 24;
    nbr = s[i++] << byte;
    byte -= 8;
    while (i < 4)
    {
        nbr += s[i] << byte;
        byte -= 8;
        i++;
    }
    return (nbr);
}

void	put_on_arena(t_cursor *cursor, t_cor *cor,
                     const unsigned char *binary, int start)
{
    int	i;

    i = cor->lev;
    while ((cor->ada * 4) > i)
    {
        if (i == cor->lev)
            start = (cursor->cci + (start % IDX_MOD)) % MEM_SIZE;
        if (cor->lev > (cor->bod = start + i))
            cor->bod = (cor->bod + MEM_SIZE);
        if (MEM_SIZE <= cor->bod)
            cor->bod = (cor->bod % MEM_SIZE);
        cor->map[cor->bod].pn = -cursor->pln;
        cor->map[cor->bod].cell = binary[i++];
    }
}

int		indir_from_cell(t_cor *cor, int start)
{
    unsigned char	str[(cor->ada * 4)];
    int i;

    i = -cor->ada;
    if (MEM_SIZE < start)
        start = (start % MEM_SIZE);
    while (++i < 4)
        str[i] = cor->map[start + i].cell;
    return (convert_chr_to_int(str));
}

void    live(t_cursor *cursor, t_cor *cor)
{
    int i;

    i = cor->lev;
    cursor->live += cor->ada;
    cor->print.nbr_live += cor->ada;
    while (i < cor->count_players)
    {
        if (cursor->op.args[cor->lev] == cor->players[i].nb)
        {
            cor->win_player = i;
            cor->players[i].last_live = cor->print.cycle;
        }
        i++;
    }
}

void    ld(t_cursor *cursor, t_cor *cor)
{
    if (check_arg(2, cursor, cor->lev))
        cursor->reg[cursor->op.args[cor->ada]] = cursor->op.args[cor->lev];
    else
    {
        if (check_arg(3, cursor, cor->lev))
            cursor->reg[cursor->op.args[cor->ada]]
                    = indir_from_cell(cor, (cursor->cci
                     + (cursor->op.args[cor->lev] % IDX_MOD)));
    }
    if (cursor->reg[cursor->op.args[cor->ada]] == cor->lev)
        cursor->carry = cor->ada;
    else
        cursor->carry = cor->lev;
}

void    st(t_cursor *cursor, t_cor *cor)
{
    int i;
    unsigned char *binary;

    if (check_arg(3, cursor, cor->ada))
    {
        i = cursor->op.args[cor->ada];
        binary = convert_int_to_str(cursor->reg[cursor->op.args[cor->lev]]);
        put_on_arena(cursor, cor, binary, i);
        free(binary);
    }
    else if (check_arg(1, cursor, cor->ada))
        cursor->reg[cursor->op.args[cor->ada]] =
                cursor->reg[cursor->op.args[cor->lev]];
}

void    add(t_cursor *cursor, t_cor *cor)
{
    cursor->reg[cursor->op.args[2]] =
            cursor->reg[cursor->op.args[cor->lev]]
            + cursor->reg[cursor->op.args[cor->ada]];
    if (cursor->reg[cursor->op.args[2]] == cor->lev)
        cursor->carry = cor->ada;
    else
        cursor->carry = cor->lev;
}

void    sub(t_cursor *cursor, t_cor *cor)
{
    cursor->reg[cursor->op.args[2]] =
            cursor->reg[cursor->op.args[cor->lev]]
            - cursor->reg[cursor->op.args[cor->ada]];
    if (cursor->reg[cursor->op.args[2]] == cor->lev)
        cursor->carry = cor->ada;
    else
        cursor->carry = cor->lev;
}

void    and(t_cursor *cursor, t_cor *cor)
{
    int i;
    int s[(cor->ada * 2)];

    i = 0;
    while (i < (cor->ada * 2))
    {
        if (check_arg(1, cursor, i))
            s[i] = cursor->reg[cursor->op.args[i]];
        else if (check_arg(2, cursor, i))
            s[i] = cursor->op.args[i];
        else if (check_arg(3, cursor, i))
            s[i] = indir_from_cell(cor,
                                      (cursor->cci + cursor->op.args[i]));
        i++;
    }
    cursor->reg[cursor->op.args[(cor->ada * 2)]] = s[cor->lev] & s[cor->ada];
    if (cursor->reg[cursor->op.args[(cor->ada * 2)]] == cor->lev)
        cursor->carry = cor->ada;
    else
        cursor->carry = cor->lev;
}

void    or(t_cursor *cursor, t_cor *cor)
{
    int i;
    int s[(cor->ada * 2)];

    i = 0;
    while (i < (cor->ada * 2))
    {
        if (check_arg(1, cursor, i))
            s[i] = cursor->reg[cursor->op.args[i]];
        else if (check_arg(2, cursor,i))
            s[i] = cursor->op.args[i];
        else if (check_arg(3, cursor, i))
            s[i] = indir_from_cell(cor,
                                   (cursor->cci + cursor->op.args[i]));
        i++;
    }
    cursor->reg[cursor->op.args[2]] = s[cor->lev] | s[cor->ada];
    if (cursor->reg[cursor->op.args[2]] == cor->lev)
        cursor->carry = cor->ada;
    else
        cursor->carry = cor->lev;
}

void    xor(t_cursor *cursor, t_cor *cor)
{
    int i;
    int s[(cor->ada * 2)];

    i = 0;
    while (i < (cor->ada * 2))
    {
        if (check_arg(1, cursor, i))
            s[i] = cursor->reg[cursor->op.args[i]];
        else if (check_arg(2, cursor, i))
            s[i] = cursor->op.args[i];
        else if (check_arg(3, cursor, i))
            s[i] = indir_from_cell(cor,
                                   (cursor->cci + cursor->op.args[i]));
        i++;
    }
    cursor->reg[cursor->op.args[2]] = s[cor->lev] ^ s[cor->ada];
    if (cursor->reg[cursor->op.args[2]] == cor->lev)
        cursor->carry = cor->ada;
    else
        cursor->carry = cor->lev;
}

void    zjump(t_cursor *cursor, t_cor *cor, int bytes)
{
    if (cursor->carry)
    {
        bytes = cursor->op.args[cor->lev] % IDX_MOD;
        cursor->sbk = bytes;
    }
}

void    ldi(t_cursor *cursor, t_cor *cor)
{
    int k;
    int s[(cor->ada * 2)];

    if (check_arg(1, cursor,cor->lev))
        s[cor->lev] = cursor->reg[cursor->op.args[cor->lev]];
    else if (check_arg(2, cursor, cor->lev))
        s[cor->lev] = cursor->op.args[cor->lev];
    else if (check_arg(3, cursor, cor->lev))
        s[cor->lev] =
                indir_from_cell(cor, cursor->cci
                                     + (cursor->cci
                                        + (cursor->op.args[cor->lev] % IDX_MOD)));
    if (check_arg(1, cursor, cor->ada))
        s[cor->ada] = cursor->reg[cursor->op.args[cor->ada]];
    else if (check_arg(2, cursor, cor->ada))
        s[cor->ada] = cursor->op.args[cor->ada];
    k = s[cor->lev] + s[cor->ada];
    k = cursor->cci + (k % IDX_MOD);
    cursor->reg[cursor->op.args[2]] = indir_from_cell(cor, k);
}

void    sti(t_cursor *cursor, t_cor *cor)
{
    int k;
    int s[(cor->ada * 2)];
    unsigned char *binary;

    if (check_arg(1, cursor, cor->ada))
        s[cor->lev] = cursor->reg[cursor->op.args[cor->ada]];
    else if (check_arg(2, cursor, cor->ada))
        s[cor->lev] = cursor->op.args[cor->ada];
    else if (check_arg(3, cursor,  cor->ada))
        s[cor->lev] = indir_from_cell(cor,
                                         cursor->cci +
                                         (cursor->op.args[cor->lev] % IDX_MOD));
    if (check_arg(1, cursor, 2))
        s[cor->ada] = cursor->reg[cursor->op.args[2]];
    else if (check_arg(2, cursor, 2))
        s[cor->ada] = cursor->op.args[2];
    k = s[cor->lev] + s[cor->ada];
    binary = convert_int_to_str(cursor->reg[cursor->op.args[cor->lev]]);
    put_on_arena(cursor, cor, binary, k);
    free(binary);
}

int    ft_fork(t_cursor *cursor, t_cor *cor)
{
    int i;
    int r;
    t_cursor	*new_carr;
    t_cursor	*old_head;

    i = (cursor->cci - cursor->sbk) + (cursor->op.args[cor->lev] % IDX_MOD);
    if (i > MEM_SIZE)
        i = i % MEM_SIZE;
    cor->players[cursor->pln - cor->ada].carr_count++;
    new_carr = (t_cursor *)malloc(sizeof(t_cursor));
    cor->cursor_cnt++;
    new_carr->pln = cursor->pln;
    new_carr->cci = i;
    new_carr->live = cursor->live;
    new_carr->carry = cursor->carry;
    r = cor->lev;
    while (++r < 17)
        new_carr->reg[r] = cursor->reg[r];
    reset_cursor(new_carr);
    old_head = cor->cursor;
    new_carr->next = old_head;
    cor->cursor = new_carr;
    return (cor->lev);
}

int    lfork(t_cursor *cursor, t_cor *cor, int i, int r)
{
    t_cursor	*new_carr;
    t_cursor	*old_head;

    i = (cursor->cci - cursor->sbk) + cursor->op.args[cor->lev];
    if (i > cor->lev)
        i = i % MEM_SIZE;
    if (i < cor->lev)
        i = MEM_SIZE + (i % MEM_SIZE);
    if (i > MEM_SIZE)
        i = i % MEM_SIZE;
    cor->players[cursor->pln - cor->ada].carr_count++;
    new_carr = (t_cursor *)malloc(sizeof(t_cursor));
    cor->cursor_cnt++;
    new_carr->pln = cursor->pln;
    new_carr->cci = i;
    new_carr->live = cursor->live;
    new_carr->carry = cursor->carry;
    while (++r < 17)
        new_carr->reg[r] = cursor->reg[r];
    reset_cursor(new_carr);
    old_head = cor->cursor;
    new_carr->next = old_head;
    cor->cursor = new_carr;
    return (cor->lev);
}

void    lld(t_cursor *cursor, t_cor *cor)
{
    if (check_arg(2, cursor,  cor->lev))
        cursor->reg[cursor->op.args[cor->ada]] = cursor->op.args[cor->lev];
    else if (check_arg(3, cursor,  cor->lev))
        cursor->reg[cursor->op.args[cor->ada]] = indir_from_cell(cor,
                                                                 (cursor->cci + cursor->op.args[cor->lev]));
    if (cursor->reg[cursor->op.args[cor->ada]] == cor->lev)
        cursor->carry = cor->ada;
    else
        cursor->carry = cor->lev;
}

void    lldi(t_cursor *cursor, t_cor *cor)
{
    int res;
    int s[(cor->ada * 2)];

    if (check_arg(1, cursor, cor->lev))
        s[cor->lev] = cursor->reg[cursor->op.args[cor->lev]];
    else if (check_arg(2, cursor, cor->lev))
        s[cor->lev] = cursor->op.args[cor->lev];
    else if (check_arg(3, cursor,  cor->lev))
        s[cor->lev] = indir_from_cell(cor, cursor->cci + cursor->op.args[cor->lev]);
    if (check_arg(1, cursor,  cor->ada))
        s[cor->ada] = cursor->reg[cursor->op.args[cor->ada]];
    else if (check_arg(2, cursor,  cor->ada))
        s[cor->ada] = cursor->op.args[cor->ada];
    s[cor->lev] = convert_uns_int((unsigned int) s[cor->lev]);
    res = s[cor->lev] + s[cor->ada];
    cursor->reg[cursor->op.args[2]] = indir_from_cell(cor, cursor->cci + res);
    if (cursor->reg[cursor->op.args[2]] == cor->lev)
        cursor->carry = cor->ada;
    else
        cursor->carry = cor->lev;
}

void    exec(t_cor *cor, t_cursor *cursor, unsigned int cd)
{
    if (cd == cor->live)
        live(cursor, cor);
    if (cd == cor->ld)
        ld(cursor, cor);
    if (cd == cor->st)
        st(cursor, cor);
    if (cd == cor->add)
        add(cursor, cor);
    if (cd == cor->sub)
        sub(cursor, cor);
    if (cd == cor->and)
        and(cursor, cor);
    if (cd == cor->or)
       or(cursor, cor);
    if (cd == cor->xor)
       xor(cursor, cor);
    if (cd == cor->zjump)
        zjump(cursor, cor, 0);
    if (cd == cor->ldi)
        ldi(cursor, cor);
    if (cd == cor->sti)
        sti(cursor, cor);
    if (cd == cor->lld)
        lld(cursor, cor);
    if (cd == cor->lldi)
        lldi(cursor, cor);
}