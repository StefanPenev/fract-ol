#ifndef FRACTOL_H
#define FRACTOL_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "libft.h"
# include "../minilibx_opengl_20191021/mlx.h"
# include "../minilibx-linux/mlx.h"

# define WIDTH 1280
# define HEIGHT 760

typedef struct s_complex
{
    double re;
    double im;
}              t_complex;

typedef struct s_data
{
    void *mlx;
    void *win;
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
    int max_iter;
    t_complex min;
    t_complex max;
    t_complex factor;
    t_complex julia_c;
    int (*fractal_func)(struct s_data *data, t_complex c);
}              t_data;


#endif
