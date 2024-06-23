/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefan <stefan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 21:00:07 by stefan            #+#    #+#             */
/*   Updated: 2024/06/23 22:08:11 by stefan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static	void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static	void	*draw_fractal_section(void *arg)
{
	t_thread_data	*thread_data;
	t_data			*data;
	int				x;
	int				y;
	t_complex		c;

	thread_data = (t_thread_data *)arg;
	data = thread_data->data;
	y = thread_data->start_y;
	while (y < thread_data->end_y)
	{
		x = 0;
		while (x < WIDTH)
		{
			c.re = data->min.re + x * data->factor.re;
			c.im = data->min.im + y * data->factor.im;
			put_pixel(data, x, y, get_color(data->fractal_func(data, c),
					data->max_iter, data->color_offset, data->color_mode));
			x++;
		}
		y++;
	}
	return (NULL);
}

static	void	create_threads(pthread_t *threads, t_thread_data *thread_data,
	t_data *data, int section_height)
{
	int	i;

	i = 0;
	while (i < NUM_THREADS)
	{
		thread_data[i].data = data;
		thread_data[i].start_y = i * section_height;
		if (i == NUM_THREADS - 1)
			thread_data[i].end_y = HEIGHT;
		else
			thread_data[i].end_y = (i + 1) * section_height;
		if (pthread_create(&threads[i], NULL, draw_fractal_section,
				&thread_data[i]))
		{
			perror("Failed to create thread");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

static	void	join_threads_and_display(pthread_t *threads, t_data *data)
{
	int	i;

	i = 0;
	while (i < NUM_THREADS)
	{
		if (pthread_join(threads[i], NULL))
		{
			perror("Failed to join thread");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

void	draw_fractal(t_data *data)
{
	pthread_t		threads[NUM_THREADS];
	t_thread_data	thread_data[NUM_THREADS];
	int				section_height;

	section_height = HEIGHT / NUM_THREADS;
	create_threads(threads, thread_data, data, section_height);
	join_threads_and_display(threads, data);
}
