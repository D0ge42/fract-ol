#include "fractol.h"
#include <X11/keysym.h>
#include <limits.h>

double map(double unscaled_num, double new_min, double new_max, double old_min, double old_max)
{
    return (new_max - new_min) * (unscaled_num - old_min) / (old_max - old_min) + new_min;
}

void my_mlx_pixel_put(f_data *img, int x, int y,  unsigned int color)
{
    char *dst;
    dst = img->img_addr + (y * img->line_lenght + x * (img->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

int apply_mandelbrot(f_data *data, int x, int y)
{
    int i = 0;
    data->zx = 0.0;
    data->zy = 0.0;
    double zx2 = 0.0;
    double zy2 = 0.0;
    data->cx = (x - WIDTH / 2.0)  /  data->zoom + data->offset_x;
    data->cy = (y - HEIGHT / 2.0) / data->zoom + data->offset_y;
    while(i <= MAX_ITERATIONS)
    {
        //Calcolo separato parte immaginaria e reale di z^2_n
        zx2 = (data->zx * data->zx) - (data->zy * data->zy) + data->cx;
        zy2 = (2 * data->zx * data->zy) + data->cy;
        //Se la norma al quadrato di z supera 4 la sequenza diverge.
        //La norma è la distanza dall'origine del punto in questione.
        //Si calcola facendo il quadrato della parte reale e immaginaria di z.
        //Controlliamo che non sfori 4 perchè di base deve restare entro +2 - 2.
        if ((zx2 * zx2) + (zy2 * zy2) > 4)
            return i;
        //Aggiorniamo z per la prossima iterazione
        data->zx = zx2;
        data->zy = zy2;
        i++;
    }
    return 0;
}

void cycle_and_apply(f_data *data,int fractal_type)
{
    int x = 0;
    int y = 0;
    int depth = 0;
    while(y < HEIGHT)
    {
        while(x < WIDTH)
        {
            if (fractal_type == MANDELBROT)
                depth = apply_mandelbrot(data,x,y);   
            if(depth)
                my_mlx_pixel_put(data,x,y,depth * data->inf_color); //Infinite values
            else
                my_mlx_pixel_put(data,x,y,depth * data->fin_color); //In-set Values
            x++;
        }
        x = 0;
        y++;
    }
}
