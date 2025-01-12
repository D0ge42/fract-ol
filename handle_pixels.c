#include "/home/doge/fract-ol/mlx/mlx.h"
#include "/home/doge/fract-ol/libft/libft.h"
#include "fractol.h"
#include <X11/keysym.h>
#include <limits.h>

double map(double unscaled_num, double new_min, double new_max, double old_min, double old_max)
{
    return (new_max - new_min) * (unscaled_num - old_min) / (old_max - old_min) + new_min;
}

int is_diverge(f_data *data, int x, int y)
{
    int i = 0;
    data->zx = 0.0;
    data->zy = 0.0;
    data->z  = 0.0;
    data->cx = map(x,(-2.0 * data->zoom),(2.0 * data->zoom),0,WIDTH);
    data->cy = map(y,(2.0 * data->zoom),(-2.0 * data->zoom),0,HEIGHT);
    while(i <= MAX_ITERATIONS)
    {
        //Calcolo separato parte immaginaria e reale di z^2_n
        double zx2 = (data->zx * data->zx) - (data->zy * data->zy) + data->cx;
        double zy2 = (2 * data->zx * data->zy) + data->cy;
        //Se la norma al quadrato di z supera 4 la sequenza diverge.
        //La norma è la distanza dall'origine del punto in questione.
        //Si calcola facendo il quadrato della parte reale e immaginaria di z.
        //Controlliamo che non sfori 4 perchè di base deve restare entro +2 - 2.
        if ((zx2 * zx2) + (zy2 * zy2) >= __DBL_MAX__)
            break;
        //Aggiorniamo z per la prossima iterazione
        data->zx = zx2;
        data->zy = zy2;

        i++;
    }
    //Se il numero delle iterazioni è uguale a max iteration il numero non diverge
    if(i ==  MAX_ITERATIONS)
        return 0;
    else
        return 1;
}

void cycle_and_apply(f_data *data)
{
    int x = 0;
    int y = 0;
    // unsigned int colors_inf[3] = {0x0fab2f9c,0x00dd1386,0x000536f3};
    // unsigned int colors_fin[3] = {0x0040190e,0x003eb56f,0x00d915f3};
    while(y < HEIGHT)
    {
        while(x < WIDTH)
        {
            if(is_diverge(data,x,y))
                my_mlx_pixel_put(data,x,y,0xFFFFFFFF);
            else
                my_mlx_pixel_put(data,x,y,0x00000000);
            x++;
        }
        x = 0;
        y++;
    }
}
