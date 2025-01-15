#include "/nfs/homes/lonulli/Fractol/libft/libft.h"
#include "/nfs/homes/lonulli/Fractol/mlx/mlx.h"
#include "fractol.h"

double	ft_atof(const char *str)
{
	double result = 0.0;
	double decimal_place = 1.0;
	int sign = 1;

	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result *  10 + (*str - '0');
		str++;
	}
	if (*str == '.')
	{
		str++;
		while (*str >= '0' && *str <= '9')
		{
			result += (*str - '0') * (decimal_place /= 10);
			str++;
		}
	}
	return (sign * result);
}

void help_menu(void)
{
		ft_printf("+--------------------------------------------+\n");
		ft_printf("|                \033[1;33m HELP MENU\033[0m                  |\n");
		ft_printf("+--------------------------------------------+\n");
		ft_printf("|--------------------------------------------|\n");
		ft_printf("|         \033[31m FOR Mandelbrot/B.Ships\033[0m            |\n");
		ft_printf("|         \033[32m ./a.out [FRACT TYPE]\033[0m              |\n");
		ft_printf("|         \033[32m./a.out Burning Ships\033[0m              |\n");
		ft_printf("|      \033[31m FOR Julia ./a.out Julia [X][Y]\033[0m       |\n");
		ft_printf("|     \033[32mX && Y should be < 2.0 && > -2.0\033[0m       |\n");
		ft_printf("|      \033[32m ./a.out Julia 0.355 0.355\033[0m            |\n");
		ft_printf("|                                            |\n");
		ft_printf("|     \033[34m Zoom IN/OUT: Mouse scroll UP/DOWN\033[0m     |\n");
		ft_printf("|  \033[34m Color SHIFT: press <a> to cycle colors\033[0m   |\n");
		ft_printf("|       \033[34m Move camera: Arrow keys\033[0m             |\n");
		ft_printf("|     \033[34m Esc/Window Cross: Quit program.\033[0m       |\n");
		ft_printf("|                                            |\n");
		ft_printf("|--------------------------------------------|\n");
}

