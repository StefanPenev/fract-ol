#include "fractol.h"

int handle_key(int key, t_data *data)
{
    if (key == 53) // ESC key
        close_window(data);
    return (0);
}

int handle_mouse(int button, int x, int y, t_data *data)
{
    if (button == 4 || button == 5) // Scroll up or down
    {
        double zoom = (button == 4) ? 1.1 : 0.9;
        double mouse_re = data->min.re + x * data->factor.re;
        double mouse_im = data->min.im + y * data->factor.im;
        data->min.re = mouse_re + (data->min.re - mouse_re) * zoom;
        data->min.im = mouse_im + (data->min.im - mouse_im) * zoom;
        data->max.re = mouse_re + (data->max.re - mouse_re) * zoom;
        data->max.im = mouse_im + (data->max.im - mouse_im) * zoom;
        data->factor = (t_complex){(data->max.re - data->min.re) / (WIDTH - 1), (data->max.im - data->min.im) / (HEIGHT - 1)};
        draw_fractal(data);
    }
    return (0);
}

int close_window(t_data *data)
{
    mlx_destroy_window(data->mlx, data->win);
    exit(0);
}
