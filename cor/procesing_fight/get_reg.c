#include "../cor.h"

int		ft_reg(t_cor *cor, t_cursor *cursor, int i, int curr_i)
{
    cursor->atp[i] = T_REG;
    if (MEM_SIZE <= curr_i)
        curr_i = (curr_i - MEM_SIZE);
    cursor->sbk += cor->ada;
    return ((int)cor->map[curr_i].cell);
}