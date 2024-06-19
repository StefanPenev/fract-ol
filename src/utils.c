#include "fractol.h"

int ft_strcmp(char *s1, char *s2)
{
	int i = 0;

	while((s1[i] == s2[i]) && s1[i] && s2[i])
		i++;
	return (s1[i]-s2[i]);
}

void usage_exemple()
{
    ft_putstr_fd("\nUsage: ./fractol \"fractal_type\"\n", 1);
    ft_putstr_fd("Available fractals: \"Mandelbrot\": ./fractol mandelbrot\n", 1);
    ft_putstr_fd("                    \"Julia\": ./fractol julia\n", 1);
    ft_putstr_fd("                    \"Julia\": ./fractol julia c_re c_im - if c_re or/and c_im are not doubles or wrong arguments, \"julia\" without arguments are rendered.\n", 1);
    ft_putstr_fd("                    \"Burning ship\": ./fractol ship\n", 1);
}

double	ft_atof(const char *str)
{
	double	res;
	double	res2;
	char	*c;
	int		len;

	c = (char *)str;
	res = (double)ft_atoi(c);
	while (*c && *c != '.')
		c++;
	if (*c == '.')
		c++;
	res2 = (double)ft_atoi(c);
	len = ft_strlen(c);
	while (len--)
		res2 /= 10;
	if (res >= 0)
		return (res + res2);
	else
		return (res + -res2);
}