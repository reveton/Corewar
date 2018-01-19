#include "../asm.h"

void    get_magic(t_asm *asem, unsigned int i)
{
    asem->magic[0] = (i >> 24) & 0xFF;
    asem->magic[1] = (i >> 16) & 0xFF;
    asem->magic[2] = (i >> 8) & 0xFF;
    asem->magic[3] = i & 0xFF;
}