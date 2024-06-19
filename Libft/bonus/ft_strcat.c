#include "libft.h"
#include <stdio.h>

char	*ft_strcat(char *s1, const char *s2)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(s1);
	j = 0;
	while (s2[j] != '\0')
	{
		s1[i + j] = s2[j];
		j++;
	}
	s1[i + j] = '\0';
	return (s1);
}

// int main()
// {
// 	char s1[] = "ala";
// 	char s2[] = "bala ";

// 	printf("%s", ft_strcat(s2, s1));
// }