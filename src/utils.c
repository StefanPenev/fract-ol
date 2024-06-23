/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefan <stefan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:16:47 by stefan            #+#    #+#             */
/*   Updated: 2024/06/23 17:36:20 by stefan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] == s2[i]) && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}

double	ft_atof(const char *str)
{
	double	whole_part;
	double	fractional_part;
	char	*c;
	int		len;

	c = (char *)str;
	whole_part = (double)ft_atoi(c);
	while (*c && *c != '.')
		c++;
	if (*c == '.')
		c++;
	fractional_part = (double)ft_atoi(c);
	len = ft_strlen(c);
	while (len--)
		fractional_part /= 10;
	if (whole_part >= 0)
		return (whole_part + fractional_part);
	else
		return (whole_part + -fractional_part);
}

void	help_msg(void)
{
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("*********************** Help *************************\n", 1);
	ft_putstr_fd("*                                                    *\n", 1);
	ft_putstr_fd("* Usage: ./fractol [mandelbrot / julia /             *\n", 1);
	ft_putstr_fd("*                   julia arg1 arg2 / ship]          *\n", 1);
	ft_putstr_fd("*                                                    *\n", 1);
	ft_putstr_fd("* e.g: ./fractol mandelbrot                          *\n", 1);
	ft_putstr_fd("* e.g: ./fractol julia -0.4 0.6                      *\n", 1);
	ft_putstr_fd("*                                                    *\n", 1);
	ft_putstr_fd("********************** KEYBOARD **********************\n", 1);
	ft_putstr_fd("*                                                    *\n", 1);
	ft_putstr_fd("* Press ESC to close the window.                     *\n", 1);
	ft_putstr_fd("* Use mouse scroll to zoom in and out of the fractal.*\n", 1);
	ft_putstr_fd("* Press the arrow keys or W,A,S,D to change the ->   *\n", 1);
	ft_putstr_fd("* -> viewpoint.                                      *\n", 1);
	ft_putstr_fd("* Press Space to reset the fractal.                  *\n", 1);
	ft_putstr_fd("* Press M to swich between gradient and smooth color.*\n", 1);
	ft_putstr_fd("* Press X, C to change color offset                  *\n", 1);
	ft_putstr_fd("*                                                    *\n", 1);
	ft_putstr_fd("******************************************************\n", 1);
	ft_putstr_fd("\n", 1);
	exit(EXIT_SUCCESS);
}
