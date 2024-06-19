#include "fractol.h"
#include <stdio.h>

void put_pixel(t_data *data, int x, int y, int color)
{
    char *dst;

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;
    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void draw_fractal(t_data *data)
{
    int x, y;
    t_complex c;

    for (y = 0; y < HEIGHT; y++)
    {
        for (x = 0; x < WIDTH; x++)
        {
            c.re = data->min.re + x * data->factor.re;
            c.im = data->min.im + y * data->factor.im;
            put_pixel(data, x, y, get_color(data->fractal_func(data, c), data->max_iter));
        }
    }
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

int mandelbrot(t_data *data, t_complex c)
{
    t_complex z = {0};
    int iter;

    for (iter = 0; iter < data->max_iter; iter++)
    {
        if (z.re * z.re + z.im * z.im > 16.0)
            break;
        z = (t_complex){
            z.re * z.re - z.im * z.im + c.re,
            2.0 * z.re * z.im + c.im
        };
    }
    return (iter);
}

int julia(t_data *data, t_complex z)
{
    int iter;

    for (iter = 0; iter < data->max_iter; iter++)
    {
        if (z.re * z.re + z.im * z.im > 4.0)
            break;
        z = (t_complex){
            z.re * z.re - z.im * z.im + data->julia_c.re,
            2.0 * z.re * z.im + data->julia_c.im
        };
    }
    return (iter);
}

int get_color(int iter, int max_iter)
{
    if (iter == max_iter)
        return (0x000000); // black for points in the set
    return (0xFFFFFF * iter / max_iter); // white gradient
}
