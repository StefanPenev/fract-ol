#include "libft.h"

/* 
	DESCRIPTION:
				The memcpy() function copies n bytes from memory area src to memory 
                area dst.  If dst and src overlap, behavior is undefined. Applications 
                in which dst and src might overlap should use memmove(3) instead.

	RETURN VALUES:
				The memcpy() function returns the original value of dst.
 */

void    *ft_memcpy(void *dst, const void *src, size_t n)
{
    size_t  i;
    char    *ptr_dst;
    char    *ptr_src;

    ptr_dst = dst;
    ptr_src = (char *)src;
    i = 0;
    while (src == NULL && dst == NULL)
        return (NULL);
    while (i < n)
    {
        ptr_dst[i] = ptr_src[i];
        i++;
    }
    return (ptr_dst);
}