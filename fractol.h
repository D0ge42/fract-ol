# ifndef FRACTOL_H
#define FRACTOL_H


#define MAX_ITERATIONS 42

typedef struct s_mlx_data
{
    void *mlx_ptr;
    void *win_ptr;
}   t_mlx_data;

typedef struct s_img_data
{
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_lenght;
    int endian;
}   t_img_data;

typedef struct c_complex
{
    double cx;
    double cy;
}   t_complex;

typedef struct s_fractal
{
    double zx;
    double zy;
    double z;
}   t_fractal;

#endif