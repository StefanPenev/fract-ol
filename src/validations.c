/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefan <stefan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 18:48:56 by stefan            #+#    #+#             */
/*   Updated: 2024/06/23 20:58:45 by stefan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static	int	validate_args(int argc, char **argv)
{
	if ((argc < 2 || (ft_strcmp(argv[1], "mandelbrot") != 0
				&& ft_strcmp(argv[1], "julia") != 0
				&& ft_strcmp(argv[1], "ship") != 0))
		|| (argc > 2 && (ft_strcmp(argv[1], "mandelbrot") == 0
				|| ft_strcmp(argv[1], "ship") == 0)))
	{
		help_msg();
		return (1);
	}
	return (0);
}

static	void	set_fractal_data(int argc, char **argv, t_data *data)
{
	if (ft_strcmp(argv[1], "mandelbrot") == 0)
	{
		data->fractal_func = mandelbrot;
		data->fractal_type = "mandelbrot";
	}
	else if (ft_strcmp(argv[1], "julia") == 0)
	{
		data->fractal_func = julia;
		data->fractal_type = "julia";
		if (argc == 4)
		{
			data->julia_c.re = atof(argv[2]);
			data->julia_c.im = atof(argv[3]);
		}
		else
			data->julia_c = (t_complex){-0.7, 0.27015};
	}
	else if (ft_strcmp(argv[1], "ship") == 0)
	{
		data->fractal_func = burning_ship;
		data->fractal_type = "ship";
	}
}

int	parse_args(int argc, char **argv, t_data *data)
{
	if (validate_args(argc, argv) != 0)
		return (1);
	set_fractal_data(argc, argv, data);
	return (0);
}
