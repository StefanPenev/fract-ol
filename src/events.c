#include "fractol.h"
#include <stdio.h>

#define ZOOM_IN_FACTOR 1.2
#define ZOOM_OUT_FACTOR 0.8
#define ITERATION_ADJUST_FACTOR 10

// void reset_view(t_data *data)
// {
//     data->max_iter = 100;  // Reset to initial iteration count
//     data->min = (t_complex){-2.0, -2.0};
//     data->max = (t_complex){2.0, 2.0};
//     data->factor = (t_complex){(data->max.re - data->min.re) / (WIDTH - 1), (data->max.im - data->min.im) / (HEIGHT - 1)};
//     draw_fractal(data); // Redraw the fractal
// }

void reset_view(t_data *data)
{
    // data->max_iter = 200;

    // // Initial center coordinates and zoom factor
    // double center_re = -0.5;
    // double center_im = 0.0;
    // double zoom_factor = 1.5;

    // // Calculate the initial range based on the zoom factor
    // double width_re = 4.0 / zoom_factor; // Initial range in the real axis
    // double height_im = 4.0 / zoom_factor * HEIGHT / WIDTH; // Maintain the aspect ratio

    // data->min.re = center_re - width_re / 2;
    // data->max.re = center_re + width_re / 2;
    // data->min.im = center_im - height_im / 2;
    // data->max.im = center_im + height_im / 2;

    // // Recalculate the scaling factors
    // data->factor = (t_complex){
    //     (data->max.re - data->min.re) / (WIDTH - 1),
    //     (data->max.im - data->min.im) / (HEIGHT - 1)
    // };
    
    draw_fractal(data); // Redraw the fractal
}


void adjust_iterations(t_data *data)
{
    if (data->zoom_factor < 1.0)
        data->max_iter = 100 + (int)(ITERATION_ADJUST_FACTOR / data->zoom_factor);
    else
        data->max_iter = 100 + (int)(data->zoom_factor * ITERATION_ADJUST_FACTOR);
}

int handle_key(int keycode, t_data *data)
{
    double move_factor_re = data->factor.re * 50;
    double move_factor_im = data->factor.im * 50;

    if (keycode == KEY_ESC)
        close_window(data);
    else if (keycode == KEY_UP || keycode == KEY_W)
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
    else if (keycode == KEY_C) // Increase color offset
        data->color_offset += 10;
    else if (keycode == KEY_X) // Decrease color offset
        data->color_offset -= 10;
    else if (keycode == KEY_M) // Switch color mode
        data->color_mode = (data->color_mode + 1) % 2; // Toggle between 0 and 1
    else if (keycode == KEY_SPACE)
        reset_view(data);

    // Recalculate factor after movement
    data->factor.re = (data->max.re - data->min.re) / (WIDTH - 1);
    data->factor.im = (data->max.im - data->min.im) / (HEIGHT - 1);

    // Redraw fractal
    draw_fractal(data);

    return 0;
}

// int handle_mouse(int button, int x, int y, t_data *data)
// {
//     double mouse_re = data->min.re + x * data->factor.re;
//     double mouse_im = data->min.im + y * data->factor.im;

//     if (button == 5)
//     {
//         data->zoom_factor *= ZOOM_IN_FACTOR;
//         data->min.re = mouse_re + (data->min.re - mouse_re) / ZOOM_IN_FACTOR;
//         data->min.im = mouse_im + (data->min.im - mouse_im) / ZOOM_IN_FACTOR;
//         data->max.re = mouse_re + (data->max.re - mouse_re) / ZOOM_IN_FACTOR;
//         data->max.im = mouse_im + (data->max.im - mouse_im) / ZOOM_IN_FACTOR;
//     }
//     else if (button == 4)
//     {
//         data->zoom_factor *= ZOOM_OUT_FACTOR;
//         data->min.re = mouse_re + (data->min.re - mouse_re) / ZOOM_OUT_FACTOR;
//         data->min.im = mouse_im + (data->min.im - mouse_im) / ZOOM_OUT_FACTOR;
//         data->max.re = mouse_re + (data->max.re - mouse_re) / ZOOM_OUT_FACTOR;
//         data->max.im = mouse_im + (data->max.im - mouse_im) / ZOOM_OUT_FACTOR;
//     }

//     // Recalculate factor after zoom
//     data->factor.re = (data->max.re - data->min.re) / (WIDTH - 1);
//     data->factor.im = (data->max.im - data->min.im) / (HEIGHT - 1);

//     // Adjust iterations based on zoom
//     adjust_iterations(data);

//     // Redraw fractal
//     draw_fractal(data);

//     return 0;
// }

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

        // Recalculate the scaling factor
        data->factor = (t_complex){
            (data->max.re - data->min.re) / (WIDTH - 1),
            (data->max.im - data->min.im) / (HEIGHT - 1)
        };

        draw_fractal(data);
    }
    return (0);
}


int close_window(t_data *data)
{
    mlx_destroy_window(data->mlx, data->win);
    exit(0);
}