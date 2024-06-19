#include "fractol.h"
#include <stdio.h>

void init_mlx(t_data *data)
{
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Fract'ol");
    data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
}

void set_defaults(t_data *data)
{
    data->max_iter = 200; // Increase max_iter for more detail
    data->min = (t_complex){-2.0, -1.5};
    data->max = (t_complex){2.0, 1.5};
    data->factor = (t_complex){(data->max.re - data->min.re) / (WIDTH - 1), (data->max.im - data->min.im) / (HEIGHT - 1)};
    data->julia_c = (t_complex){-0.7, 0.27015}; // Example value for Julia set
}

int main(int argc, char **argv)
{
    t_data data;

    if (argc != 2 || (ft_strncmp(argv[1], "mandelbrot", 10) != 0 && ft_strncmp(argv[1], "julia", 5) != 0))
    {
        printf("Usage: %s <mandelbrot/julia>\n", argv[0]);
        return (1);
    }
    init_mlx(&data);
    set_defaults(&data);
    if (ft_strncmp(argv[1], "mandelbrot", 10) == 0)
        data.fractal_func = mandelbrot;
    else
        data.fractal_func = julia;
    draw_fractal(&data);
    mlx_key_hook(data.win, handle_key, &data);
    mlx_mouse_hook(data.win, handle_mouse, &data);
    mlx_hook(data.win, 17, 0, close_window, &data); // Handle window close
    mlx_loop(data.mlx);
    return (0);
}