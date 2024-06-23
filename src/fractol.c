/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefan <stefan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:05:00 by spenev            #+#    #+#             */
/*   Updated: 2024/06/23 21:02:33 by stefan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	mandelbrot(t_data *data, t_complex c)
{
	t_complex	z;
	int			iter;

	z.re = 0;
	z.im = 0;
	iter = 0;
	while (iter < data->max_iter)
	{
		if (z.re * z.re + z.im * z.im > 16.0)
			break ;
		z = (t_complex){
			z.re * z.re - z.im * z.im + c.re,
			2.0 * z.re * z.im + c.im
		};
		iter++;
	}
	return (iter);
}

int	julia(t_data *data, t_complex z)
{
	int	iter;

	z.im = -z.im;
	iter = 0;
	while (iter < data->max_iter)
	{
		if (z.re * z.re + z.im * z.im > 4.0)
			break ;
		z = (t_complex){
			z.re * z.re - z.im * z.im + data->julia_c.re,
			2.0 * z.re * z.im + data->julia_c.im
		};
		iter++;
	}
	return (iter);
}

int	burning_ship(t_data *data, t_complex c)
{
	t_complex	z;
	int			iter;

	z.re = 0;
	z.im = 0;
	iter = 0;
	while (iter < data->max_iter)
	{
		if (z.re * z.re + z.im * z.im > 4.0)
			break ;
		z = (t_complex){
			fabs(z.re) * fabs(z.re) - fabs(z.im) * fabs(z.im) + c.re,
			2.0 * fabs(z.re) * fabs(z.im) + c.im
		};
		iter++;
	}
	return (iter);
}
