#include "libft.h"

void    ft_strclr(char *s)
{
    if(s)
        while (*s)
            *s++ = '\0';
}

// int main()
// {
//     char str[] = {'h', 'e', 'l', 'l', 'o'};
//     printf("before -> %s\n", str);
//     ft_strclr(str);
//     printf("after -> %s", str);
//     return (0);
// }