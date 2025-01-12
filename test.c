#include "/home/doge/fract-ol/mlx/mlx.h"
#include "/home/doge/fract-ol/libft/libft.h"
#include "fractol.h"
#include <X11/keysym.h>

int handle_input(int keycode, f_data *data)
{
    if (keycode == XK_Escape)
    {
        mlx_destroy_display(data->mlx_ptr);
        mlx_destroy_window(data->mlx_ptr,data->win_ptr);
        free(data->mlx_ptr);
        exit(0);
    }
    ft_printf("The %d key has been pressed\n\n",keycode);
    return 0;
}

int zoom_in_and_out(int keycode, int x, int y, f_data *data)
{
    if(keycode == WHEEL_UP)
        data->zoom *=1.1312312321;
    else if (keycode == WHEEL_DOWN)
        data->zoom /= 1.1312312321;
    cycle_and_apply(data);
    return 0;
}


void my_mlx_pixel_put(f_data *img, int x, int y,  int color)
{
    char *dst;
    dst = img->img_addr + (y * img->line_lenght + x * (img->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

int main() 
{
    f_data data;
    data.zoom = 1.0;
    // Initialize the connection to the X server
    data.mlx_ptr = mlx_init();
    if(!data.mlx_ptr)
        return 1;

    // Create window
    data.win_ptr = mlx_new_window(data.mlx_ptr,WIDTH,HEIGHT,"FRACTOL");

    //Img creation
    data.img = mlx_new_image(data.mlx_ptr,WIDTH,HEIGHT);

    data.img_addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_lenght, &data.endian);


    mlx_mouse_hook(data.win_ptr,zoom_in_and_out,&data);

    //Clean exit
    mlx_key_hook(data.win_ptr,handle_input,&data);
    
    mlx_put_image_to_window(data.mlx_ptr,data.win_ptr,data.img,0,0);

    // To keep the window alive we've t use mix_loop.
    mlx_loop(data.mlx_ptr);

    return 0;
}
