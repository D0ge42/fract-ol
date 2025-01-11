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

void my_mlx_pixel_put(t_img_data *img, int x, int y, int color)
{
    char *dst;
    dst = img->addr + (y * img->line_lenght + x * (img->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

int main() 
{
    t_mlx_data data;
    t_img_data img;

    // Initialize the connection to the X server
    data.mlx_ptr = mlx_init();
    if(!data.mlx_ptr)
        return 1;

    // Create window
    data.win_ptr = mlx_new_window(data.mlx_ptr,1280,720,"FRACTOL");

    //Img creation
    img.img = mlx_new_image(data.mlx_ptr,1280,720);

    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_lenght, &img.endian);

    my_mlx_pixel_put(&img,30,30,0x00FFFF00);
    
    mlx_put_image_to_window(data.mlx_ptr,data.win_ptr,img.img,0,0);

    // Handle clean exit.
    mlx_key_hook(data.win_ptr,handle_input,&data);



    // To keep the window alive we've t use mix_loop.
    mlx_loop(data.mlx_ptr);

    return 0;
}
