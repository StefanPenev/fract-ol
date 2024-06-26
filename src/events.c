/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spenev <spenev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:50:10 by spenev            #+#    #+#             */
/*   Updated: 2024/06/26 12:40:23 by spenev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	adjust_iterations(t_data *data)
{
	int	max_iter;

	if (data->zoom_factor < 1.0)
	{
		max_iter = 100 + (int)(ITERATION_ADJUST_FACTOR / data->zoom_factor);
		data->max_iter = max_iter;
	}
	else
	{
		max_iter = 100 + (int)(data->zoom_factor * ITERATION_ADJUST_FACTOR);
		data->max_iter = max_iter;
	}
}

static	void	handle_movement_keys(int keycode, t_data *data)
{
	double	move_factor_re;
	double	move_factor_im;

	move_factor_re = data->factor.re * 50;
	move_factor_im = data->factor.im * 50;
	if (keycode == KEY_UP || keycode == KEY_W)
	{
		data->min.im -= move_factor_im;
		data->max.im -= move_factor_im;
	}
	else if (keycode == KEY_DOWN || keycode == KEY_S)
	{
		data->min.im += move_factor_im;
		data->max.im += move_factor_im;
	}
	else if (keycode == KEY_LEFT || keycode == KEY_A)
	{
		data->min.re -= move_factor_re;
		data->max.re -= move_factor_re;
	}
	else if (keycode == KEY_RIGHT || keycode == KEY_D)
	{
		data->min.re += move_factor_re;
		data->max.re += move_factor_re;
	}
}

int	handle_key(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		close_window(data);
	else if (keycode == KEY_UP || keycode == KEY_W
		|| keycode == KEY_DOWN || keycode == KEY_S
		|| keycode == KEY_LEFT || keycode == KEY_A
		|| keycode == KEY_RIGHT || keycode == KEY_D)
	{
		handle_movement_keys(keycode, data);
	}
	else if (keycode == KEY_C)
		data->color_offset += 10;
	else if (keycode == KEY_X)
		data->color_offset -= 10;
	else if (keycode == KEY_M)
		data->color_mode = (data->color_mode + 1) % 2;
	else if (keycode == KEY_SPACE)
		set_defaults(data, data->fractal_type);
	data->factor.re = (data->max.re - data->min.re) / (WIDTH - 1);
	data->factor.im = (data->max.im - data->min.im) / (HEIGHT - 1);
	draw_fractal(data);
	return (0);
}

int	handle_mouse(int button, int x, int y, t_data *data)
{
	double	zoom;
	double	mouse_re;
	double	mouse_im;

	if (button == 5 || button == 4)
	{
		if (button == 4)
			zoom = 0.9;
		else
			zoom = 1.1;
		mouse_re = data->min.re + x * data->factor.re;
		mouse_im = data->min.im + y * data->factor.im;
		data->min.re = mouse_re + (data->min.re - mouse_re) * zoom;
		data->min.im = mouse_im + (data->min.im - mouse_im) * zoom;
		data->max.re = mouse_re + (data->max.re - mouse_re) * zoom;
		data->max.im = mouse_im + (data->max.im - mouse_im) * zoom;
		data->factor = (t_complex)
		{
			(data->max.re - data->min.re) / (WIDTH - 1),
			(data->max.im - data->min.im) / (HEIGHT - 1)
		};
		draw_fractal(data);
	}
	return (0);
}

int	close_window(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
}
