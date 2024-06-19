#include <math.h>

typedef struct s_rgb
{
    int r;
    int g;
    int b;
}              t_rgb;

t_rgb hsv_to_rgb(double h, double s, double v)
{
    double p, q, t, ff;
    long i;
    t_rgb rgb;

    if (s <= 0.0)
    {
        rgb.r = v * 255;
        rgb.g = v * 255;
        rgb.b = v * 255;
        return rgb;
    }
    h /= 60.0;
    i = (long)h;
    ff = h - i;
    p = v * (1.0 - s);
    q = v * (1.0 - (s * ff));
    t = v * (1.0 - (s * (1.0 - ff)));

    switch (i)
    {
        case 0:
            rgb.r = v * 255;
            rgb.g = t * 255;
            rgb.b = p * 255;
            break;
        case 1:
            rgb.r = q * 255;
            rgb.g = v * 255;
            rgb.b = p * 255;
            break;
        case 2:
            rgb.r = p * 255;
            rgb.g = v * 255;
            rgb.b = t * 255;
            break;
        case 3:
            rgb.r = p * 255;
            rgb.g = q * 255;
            rgb.b = v * 255;
            break;
        case 4:
            rgb.r = t * 255;
            rgb.g = p * 255;
            rgb.b = v * 255;
            break;
        case 5:
        default:
            rgb.r = v * 255;
            rgb.g = p * 255;
            rgb.b = q * 255;
            break;
    }
    return rgb;
}

int get_color(int iter, int max_iter)
{
    if (iter == max_iter)
        return (0x000000); // black for points in the set

    double t = (double)iter / (double)max_iter;
    double hue = 360.0 * t;  // Hue cycle from 0 to 360
    double saturation = 1.0; // Full saturation for vibrant colors
    double value = 1.0;      // Full value for brightness

    t_rgb rgb = hsv_to_rgb(hue, saturation, value);
    return ((rgb.r << 16) | (rgb.g << 8) | rgb.b);
}

// int get_color(int iter, int max_iter, int color_offset, int color_mode)
// {
//     if (iter == max_iter)
//         return 0x000000; // Black for points inside the fractal
    
//     double color;
//     if (color_mode == 0) // Gradient color mode
//     {
//         int red = (iter * 5 + color_offset) % 256;
//         int green = (iter * 10 + color_offset) % 256;
//         int blue = (iter * 20 + color_offset) % 256;
//         color = (red << 16) | (green << 8) | blue;
//     }
//     else // Smooth color mode
//     {
//         double t = (double)iter / (double)max_iter;
//         int red = (int)(9 * (1 - t) * t * t * t * 255) % 256;
//         int green = (int)(15 * (1 - t) * (1 - t) * t * t * 255) % 256;
//         int blue = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255) % 256;
//         color = (red << 16) | (green << 8) | blue;
//     }
//     return color;
// }
