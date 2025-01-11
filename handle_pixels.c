#include "/home/doge/fract-ol/mlx/mlx.h"
#include "/home/doge/fract-ol/libft/libft.h"
#include "fractol.h"
#include <X11/keysym.h>

double map(double unscaled_num, double new_min, double new_max, double old_min, double old_max)
{
    return (new_max - new_min) * (unscaled_num - old_min) / (old_max - old_min) + new_min;
}

void apply_mandlebrot(t_img_data *img,t_fractal *fract,t_complex *complex, double x, double y)
{
    unsigned int colors_inf[3] = {0x0fab2f9c,0x00dd1386,0x000536f3};
    unsigned int colors_fin[3] = {0x0040190e,0x003eb56f,0x00d915f3};
    double temp = 0.0;
    double temp_res = 0.0;
    int i = 0;
    //Ottengo zx e zy applicando map alle coordinate del pixel
    fract->zx = 0.0;
    fract->zy = 0.0;
    fract->z  = 0.0;
    complex->cx = map(x,-2,+2,0,1280);
    complex->cy = map(y,+2,-2,0,720);
    while(i <= MAX_ITERATIONS)
    {
        //Calcolo separato parte immaginaria e reale di z^2_n
        double zx2 = (fract->zx * fract->zx) - (fract->zy * fract->zy) + complex->cx;
        double zy2 = (2 * (fract->zx) * (fract->zy)) + complex->cy;
        //Se la norma al quadrato di z supera 4 la sequenza diverge.
        //La norma è la distanza dall'origine del punto in questione.
        //Si calcola facendo il quadrato della parte reale e immaginaria di z.
        //Controlliamo che non sfori 4 perchè di base deve restare entro +2 - 2.
        if ((zx2 * zx2) + (zy2 * zy2) > 4)
            break;

        //Aggiorniamo z per la prossima iterazione
        fract->zx = zx2;
        fract->zy = zy2;

        i++;
    }
    //Se il numero delle iterazioni è uguale a max iteration il numero non diverge
    //Se è minore si.
}