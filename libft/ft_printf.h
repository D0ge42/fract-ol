/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:16:17 by lonulli           #+#    #+#             */
/*   Updated: 2025/01/07 09:16:18 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <limits.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/*Main structure. Handles everything as if each variable is a light switch.
Depending on if it's turned on or off a different output will be produced*/

typedef struct s_format
{
	int		minus;
	int		hashtag;
	int		plus;
	int		space;
	int		zero;
	int		width;
	int		precision;
	char	conversion;
}			t_format;

/*Utils*/

int			ft_strlen(char *str);
int			is_conversion(char c);
int			is_flag(char c);
int			is_digit(char c);
int			perc_counter(char c, const char *str);
int			count_digits(long long num);
int			count_hex_digits(unsigned int num);
int			count_memory_address_length(unsigned long long ptr);
int			max(int a, int b);
int			count_udigits(unsigned int num);
int			ft_atoi(const char *str);
int			ft_strchr(char c, const char *str);
void		jump_index(const char *format, int *i);
void		space_writer(int spaces, int *count);
void		zero_writer(int zeros, int *count);
void		free_structs(t_format **struct_array, const char *format);
void		initialize_struct(t_format *new_s);

/*Main function*/

int			ft_printf(const char *format, ...);

/*Different types paddings*/

void		id_left_padding(t_format *new_s, long long nb, int *count,
				int spaces);
void		id_right_padding(t_format *new_s, long long nb, int *count,
				int spaces);
void		id_no_padding(t_format *new_s, long long nb, int *count);
void		u_left_padding(t_format *new_s, unsigned int nb, int *count,
				int spaces);
void		u_right_padding(t_format *new_s, unsigned int nb, int *count,
				int spaces);
void		u_no_padding(t_format *new_s, unsigned int nb, int *count);
void		hexa_left_padding(t_format *new_s, unsigned int nb, int *count,
				int spaces);
void		hexa_right_padding(t_format *new_s, unsigned int nb, int *count,
				int spaces);
void		hexa_no_padding(t_format *new_s, unsigned int nb, int *count);
void		p_left_padding(t_format *new_s, unsigned long long nb, int *count,
				int spaces);
void		p_right_padding(t_format *new_s, unsigned long long nb, int *count,
				int spaces);
void		p_no_padding(t_format *new_s, unsigned long long nb, int *count);

/*Handlers*/
void		string_handler(t_format *new_s, va_list args, int *count);
void		char_handler(t_format *new_s, va_list args, int *count);
void		int_handler(t_format *new_s, va_list args, int *count);
void		uint_handler(t_format *new_s, va_list args, int *count);
void		hexa_handler(t_format *new_s, va_list args, int *count);
void		p_handler(t_format *new_s, va_list args, int *count);

/*Printers*/
void		ft_print_pointer(uintptr_t nb, int *count);
void		ft_print_hexa(unsigned int nb, int *count, char c);
void		ft_printnb_count(long long int nb, int *count, t_format *new_s);
void		ft_printunb_count(unsigned int nb, int *count);
void		ft_putstr_count(void *str2, int *count, t_format *new_s, int len);
void		ft_putchar_count(char c, int *count);
void		space_writer(int spaces, int *count);
void		zero_writer(int zeros, int *count);
void		ft_putstr(char *str);

/*Struct handleer*/

void		struct_to_string(t_format *new_s, va_list args, int *count);
t_format	*create_struct(const char *format);
t_format	**create_struct_array(const char *format);
void		get_flags(t_format *new_s, const char *format);
int			get_width(const char *format);
int			get_precision(const char *format);
void		get_conversion(const char *format, t_format *new_s);

#endif
