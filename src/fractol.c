/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spenev <spenev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:05:00 by spenev            #+#    #+#             */
/*   Updated: 2024/06/20 13:33:14 by spenev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	*draw_fractal_section(void *arg)
{
	t_thread_data	*thread_data = (t_thread_data *)arg;
	t_data			*data = thread_data->data;
	int				x;
	int				y;
	t_complex		c;

	for (y = thread_data->start_y; y < thread_data->end_y; y++)
	{
		for (x = 0; x < WIDTH; x++)
		{
			c.re = data->min.re + x * data->factor.re;
			c.im = data->min.im + y * data->factor.im;
			put_pixel(data, x, y, get_color(data->fractal_func(data, c), data->max_iter, data->color_offset, data->color_mode));
		}
	}
	return (NULL);
}

void draw_fractal(t_data *data)
{
    pthread_t threads[NUM_THREADS];
    t_thread_data thread_data[NUM_THREADS];
    int i;

    // Divide the image into sections
    int section_height = HEIGHT / NUM_THREADS;

    for (i = 0; i < NUM_THREADS; i++)
    {
        thread_data[i].data = data;
        thread_data[i].start_y = i * section_height;
        thread_data[i].end_y = (i == NUM_THREADS - 1) ? HEIGHT : (i + 1) * section_height;
        if (pthread_create(&threads[i], NULL, draw_fractal_section, &thread_data[i]))
        {
            perror("Failed to create thread");
            exit(EXIT_FAILURE);
        }
    }

    // Join all threads
    for (i = 0; i < NUM_THREADS; i++)
    {
        if (pthread_join(threads[i], NULL))
        {
            perror("Failed to join thread");
            exit(EXIT_FAILURE);
        }
    }

    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

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
