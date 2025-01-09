#include "/home/doge/fract-ol/mlx/mlx.h"
#include "/home/doge/fract-ol/libft/libft.h"
#include "fractol.h"
#include <X11/keysym.h>

int handle_input(int keycode, t_mlx_data *data)
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

int main() 
{
    t_mlx_data data;

    // Initialize the connection to the X server
    data.mlx_ptr = mlx_init();
    if(!data.mlx_ptr)
        return 1;

    // Create window
    mlx_new_window(data.mlx_ptr,1280,720,"FRACTOL");

    mlx_key_hook(data.win_ptr,handle_input,&data);

    // To keep the window alive we've t use mix_loop.
    mlx_loop(data.mlx_ptr);

    return 0;
}
