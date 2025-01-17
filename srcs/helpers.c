/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 10:56:09 by lonulli           #+#    #+#             */
/*   Updated: 2025/01/16 10:56:11 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	skip_white_spaces(const char *str, int *i)
{
	while (str[*i] == 32 || (str[*i] >= 9 && str[*i] <= 13))
		(*i)++;
}

int	count_dots(const char *str, char c)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == c)
			count++;
		str++;
	}
	return (count);
}

static double	*handle_sign(const char *str, int *i, double *sign)
{
	int	j;

	j = 0;
	*sign = 1.0;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[(*i)++] == '-')
			*sign = -1.0;
		if (str[*i] == '-' || str[*i] == '+')
		{
			*sign = -2.1;
			return (sign);
		}
	}
	skip_white_spaces(str, i);
	j = *i;
	while (str[j])
	{
		if ((!is_digit(str[j]) && str[j] != '.') || (count_dots(str, '.') > 1))
			*sign = -2.1;
		j++;
	}
	return (sign);
}

double	ft_atof(const char *str)
{
	double	result;
	double	decimal_place;
	double	sign;
	int		i;

	i = 0;
	result = 0.0;
	decimal_place = 1.0;
	skip_white_spaces(str, &i);
	sign = *(handle_sign(str, &i, &sign));
	if (sign == -2.1)
		return (sign);
	while (str[i] >= '0' && str[i] <= '9')
		result = result * 10 + (str[i++] - '0');
	if (str[i++] == '.')
	{
		if (!(is_digit(str[i])))
			return (-2.1);
		while (str[i] >= '0' && str[i] <= '9')
		{
			result += (str[i++] - '0') * (decimal_place / 10);
			decimal_place /= 10;
		}
	}
	return (sign * result);
}

void	help_menu(void)
{
	ft_printf("+-------------------------------------+\n");
	ft_printf("|            \033[1;33m HELP MENU\033[0m               |\n");
	ft_printf("+-------------------------------------+\n");
	ft_printf("|      \033[31m FOR Mandelbrot/B.Ships\033[0m        |\n");
	ft_printf("|      \033[32m ./a.out [FRACT TYPE]\033[0m          |\n");
	ft_printf("|      \033[32m./a.out Burning Ships\033[0m          |\n");
	ft_printf("|                                     |\n");
	ft_printf("|   \033[31m FOR Julia ./a.out Julia [X][Y]\033[0m   |\n");
	ft_printf("|   \033[32mX && Y should be < 2.0 && >-2.0\033[0m   |\n");
	ft_printf("|    \033[32m ./a.out Julia 0.355 0.355\033[0m       |\n");
	ft_printf("|                                     |\n");
	ft_printf("| \033[34m Zoom IN/OUT: Mouse scroll UP/DOWN\033[0m  |\n");
	ft_printf("|  \033[34m Color SHIFT: <a> to cycle colors\033[0m  |\n");
	ft_printf("|    \033[34m Move camera: Arrow keys\033[0m         |\n");
	ft_printf("|  \033[34m Esc/Window Cross: Quit program.\033[0m   |\n");
	ft_printf("|_____________________________________|\n");
}
