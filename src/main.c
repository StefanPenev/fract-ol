#include "../includes/fractol.h"

void init_mlx(t_data *data)
{
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Fract'ol");
    data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
}

void set_defaults(t_data *data, char *fractal_type)
{
    data->max_iter = 200;

    double center_re = 0.0;
    double center_im = 0.0;
    double zoom_factor = 0.0;

    if (center_re == 0.0 && center_im == 0.0 && zoom_factor == 0.0)
    {
        if (ft_strcmp(fractal_type, "mandelbrot") == 0)
        {
            center_re = -0.5;
            center_im = 0.0;
            zoom_factor = 1.5;
        }
        else if (ft_strcmp(fractal_type, "julia") == 0)
        {
            center_re = 0.0;
            center_im = 0.0;
            zoom_factor = 1.2; 
        }
        else if (ft_strcmp(fractal_type, "ship") == 0)
        {
            center_re = -0.2;
            center_im = -0.5;
            zoom_factor = 1.2;
        }
    }

    double width_re = 4.0 / zoom_factor; 
    double height_im = 4.0 / zoom_factor * HEIGHT / WIDTH; 

    data->min.re = center_re - width_re / 2;
    data->max.re = center_re + width_re / 2;
    data->min.im = center_im - height_im / 2;
    data->max.im = center_im + height_im / 2;

    data->factor = (t_complex){
        (data->max.re - data->min.re) / (WIDTH - 1),
        (data->max.im - data->min.im) / (HEIGHT - 1)
    };
}

int parse_args(int argc, char **argv, t_data *data)
{
    if (argc < 2 || (ft_strcmp(argv[1], "mandelbrot") != 0 && ft_strcmp(argv[1], "julia") != 0 && ft_strcmp(argv[1], "ship") != 0))
    {
        usage_exemple();
        return (1);
    }
    if (ft_strcmp(argv[1], "mandelbrot") == 0)
    {
        data->fractal_func = mandelbrot;
        data->fractal_type = "mandelbrot";
    }
    else if (ft_strcmp(argv[1], "julia") == 0)
    {
        data->fractal_func = julia;
        data->fractal_type = "julia";
        if (argc == 4)
        {
            data->julia_c.re = atof(argv[2]);
            data->julia_c.im = atof(argv[3]);
        }
        else
            data->julia_c = (t_complex){-0.7, 0.27015};
    }
    else if (ft_strcmp(argv[1], "ship") == 0)
    {
        data->fractal_func = burning_ship;
        data->fractal_type = "ship";
    }
    return (0);
}

int main(int argc, char **argv)
{
   t_data data;

    set_defaults(&data, argv[1]);
    if (parse_args(argc, argv, &data) != 0)
        return 1;
    init_mlx(&data);
    draw_fractal(&data);
    mlx_key_hook(data.win, handle_key, &data);
    mlx_mouse_hook(data.win, handle_mouse, &data);
    mlx_hook(data.win, 17, 0, close_window, &data);
    mlx_loop(data.mlx);
    return (0);
}
