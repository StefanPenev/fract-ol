/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defaults.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefan <stefan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 18:37:44 by stefan            #+#    #+#             */
/*   Updated: 2024/06/23 18:54:03 by stefan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static	void	set_fractal_defaults(char *fractal_type, double *center_re,
	double *center_im, double *zoom_factor)
{
	if (*center_re == 0.0 && *center_im == 0.0 && *zoom_factor == 0.0)
	{
		if (ft_strcmp(fractal_type, "mandelbrot") == 0)
		{
			*center_re = -0.5;
			*center_im = 0.0;
			*zoom_factor = 1.5;
		}
		else if (ft_strcmp(fractal_type, "julia") == 0)
		{
			*center_re = 0.0;
			*center_im = 0.0;
			*zoom_factor = 1.2;
		}
		else if (ft_strcmp(fractal_type, "ship") == 0)
		{
			*center_re = -0.2;
			*center_im = -0.5;
			*zoom_factor = 1.2;
		}
	}
}

static	void	set_basic_parameters(t_data *data)
{
	data->max_iter = 200;
	data->min = (t_complex){-2.0, -2.0};
	data->max = (t_complex){2.0, 2.0};
	data->color_mode = 0;
	data->color_offset = 0;
}

static	void	calculate_parameters(t_data *data, double center_re,
	double center_im, double zoom_factor)
{
	double	width_re;
	double	height_im;

	width_re = 4.0 / zoom_factor;
	height_im = 4.0 / zoom_factor * HEIGHT / WIDTH;

	data->min.re = center_re - width_re / 2;
	data->max.re = center_re + width_re / 2;
	data->min.im = center_im - height_im / 2;
	data->max.im = center_im + height_im / 2;

	data->factor = (t_complex){
		(data->max.re - data->min.re) / (WIDTH - 1),
		(data->max.im - data->min.im) / (HEIGHT - 1)
	};
}

void	set_defaults(t_data *data, char *fractal_type)
{
	double	center_re;
	double	center_im;
	double	zoom_factor;

	center_re = 0.0;
	center_im = 0.0;
	zoom_factor = 0.0;
	set_basic_parameters(data);
	set_fractal_defaults(fractal_type, &center_re, &center_im, &zoom_factor);
	calculate_parameters(data, center_re, center_im, zoom_factor);
}
