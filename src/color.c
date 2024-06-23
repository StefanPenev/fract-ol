/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spenev <spenev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:43:21 by spenev            #+#    #+#             */
/*   Updated: 2024/06/20 11:48:08 by spenev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	get_color(int iter, int max_iter, int color_offset, int color_mode)
{
	double	color;
	int		red;
	int		green;
	int		blue;
	double	t;

	if (iter == max_iter)
		return (0x000000);
	if (color_mode == 0)
	{
		red = (iter * 5 + color_offset) % 256;
		green = (iter * 10 + color_offset) % 256;
		blue = (iter * 20 + color_offset) % 256;
		color = (red << 16) | (green << 8) | blue;
	}
	else
	{
		t = (double)iter / (double)max_iter;
		red = (int)(9 * (1 - t) * t * t * t * 255) % 256;
		green = (int)(15 * (1 - t) * (1 - t) * t * t * 255) % 256;
		blue = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255) % 256;
		color = (red << 16) | (green << 8) | blue;
	}
	return (color);
}
