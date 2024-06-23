#include "../includes/fractol.h"

int ft_strcmp(char *s1, char *s2)
{
	int i = 0;

	while((s1[i] == s2[i]) && s1[i] && s2[i])
		i++;
	return (s1[i]-s2[i]);
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

void	help_msg(void)
{
	ft_putstr_fd("\n", 1);
	ft_putstr_fd(" ************************** Help ***************************\n", 1);
	ft_putstr_fd(" *                                                         *\n", 1);
	ft_putstr_fd(" * Usage: ./fractol [mandelbrot / julia / julia arg1 arg2  *\n", 1);
	ft_putstr_fd(" *                   / ship]                               *\n", 1);
	ft_putstr_fd(" *                                                         *\n", 1);
	ft_putstr_fd(" * e.g: ./fractol mandelbrot                               *\n", 1);
	ft_putstr_fd(" * e.g: ./fractol julia -0.4 0.6                           *\n", 1);
	ft_putstr_fd(" *                                                         *\n", 1);
	ft_putstr_fd(" ************************ KEYBOARD *************************\n", 1);
	ft_putstr_fd(" *                                                         *\n", 1);
	ft_putstr_fd(" * Press ESC to close the window.                          *\n", 1);
	ft_putstr_fd(" * Use mouse scroll to zoom in and out of the fractal.     *\n", 1);
	ft_putstr_fd(" * Press the arrow keys or W,A,S,D to change the viewpoint.*\n", 1);
	ft_putstr_fd(" * Press Space to reset the fractal.                       *\n", 1);
	ft_putstr_fd(" * Press M to swich between gradient and smooth color.     *\n", 1);
	ft_putstr_fd(" * Press X, C to change color offset                       *\n", 1);
	ft_putstr_fd(" *                                                         *\n", 1);
	ft_putstr_fd(" ***********************************************************\n", 1);
	ft_putstr_fd("\n", 1);
	exit(EXIT_SUCCESS);
}
