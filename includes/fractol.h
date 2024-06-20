/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spenev <spenev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:28:50 by spenev            #+#    #+#             */
/*   Updated: 2024/06/20 11:33:49 by spenev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "../Libft/libft.h"
# include "../minilibx_opengl_20191021/mlx.h"
# include "../minilibx-linux/mlx.h"
# include "keycodes.h"
# include <pthread.h>

# define WIDTH 800
# define HEIGHT 600
# define NUM_THREADS 8

typedef struct s_complex
{
	double	re;
	double	im;
}			t_complex;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_complex	min;
	t_complex	max;
	t_complex	factor;
	t_complex	julia_c;
	int			max_iter;
	double		escape_radius;
	int			(*fractal_func)(struct s_data *data, t_complex c);
	int			color_offset;
	int			color_mode;
	double		zoom_factor;
}			t_data;

typedef struct s_thread_data
{
	t_data	*data;
	int		start_y;
	int		end_y;
}				t_thread_data;

void	draw_fractal(t_data *data);
int		mandelbrot(t_data *data, t_complex c);
int		julia(t_data *data, t_complex c);
int		handle_key(int key, t_data *data);
int		handle_mouse(int button, int x, int y, t_data *data);
int		close_window(t_data *data);
void	put_pixel(t_data *data, int x, int y, int color);
int		get_color(int iter, int max_iter, int color_offset, int color_mode);
//int get_color(int iter, int max_iter);
int		parse_args(int argc, char **argv, t_data *data);
int		burning_ship(t_data *data, t_complex c);
int		ft_strcmp(char *s1, char *s2);
void	usage_exemple(void);
double	ft_atof(const char *str);

#endif
