#include "minishell.h"

int ft_isprint_byte(int c)
{
    unsigned char uc;

    uc = (unsigned char) c;
    return (uc >= 32 && uc != 127);
}
