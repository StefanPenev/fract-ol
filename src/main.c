/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefan <stefan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:36:56 by stefan            #+#    #+#             */
/*   Updated: 2024/06/23 19:00:30 by stefan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Fract'ol");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (parse_args(argc, argv, &data) != 0)
		return (1);
	set_defaults(&data, argv[1]);
	init_mlx(&data);
	draw_fractal(&data);
	mlx_key_hook(data.win, handle_key, &data);
	mlx_mouse_hook(data.win, handle_mouse, &data);
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}
