/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lonulli <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:16:06 by lonulli           #+#    #+#             */
/*   Updated: 2025/01/07 09:16:08 by lonulli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*ft_printf workflow
1) Create a struct array. Number of struct depends on number of %
2) Each struct will be filled with specific info of current %.
3) From each struct we'll print the resulting string,
made of different,flags,width,precision and conversion*/

int	ft_printf(const char *format, ...)
{
	int			j;
	int			i;
	int			count;
	va_list		args;
	t_format	**struct_array;

	j = 0;
	i = 0;
	count = 0;
	struct_array = create_struct_array(format);
	va_start(args, format);
	while (format[i] && struct_array)
	{
		if (format[i] == '%')
		{
			struct_to_string(struct_array[j++], args, &count);
			jump_index(format, &i);
		}
		else if (format[i])
			ft_putchar_count(format[i++], &count);
	}
	free_structs(struct_array, format);
	va_end(args);
	return (count);
}

// #include "ft_printf.h"
// #include <limits.h>
// #include <stdio.h>
// void    test_return_values(int org, int ft, int test_number)
// {
//     if (org == ft)
//         printf("\033[0;32mTest %d: OK - Return values match: %d\033[0m\n",
//             test_number, org);
//     else
//         printf("\033[0;31mTest %d: KO - Expected: %d, Got: %d\033[0m\n",
//             test_number, org, ft);
// }
// int main(void)
// {
//     int     org;
//     int     ft;
//     int     test_num;
//     int     num;
//     void    *ptr;
//     void    *null_ptr;
//     test_num = 1;
//     printf("\n=== TESTING %%c ===\n");
//     // %c only works with width and minus flag
//     printf("\nTest %d: Basic char\n", test_num);
//     org = printf("Printf:    |%c|\n", 'a');
//     ft = ft_printf("ft_printf: |%c|\n", 'a');
//     test_return_values(org, ft, test_num++);
//     printf("\nTest %d: Width\n", test_num);
//     org = printf("Printf:    |%5c|\n", 'a');
//     ft = ft_printf("ft_printf: |%5c|\n", 'a');
//     test_return_values(org, ft, test_num++);
//     printf("\nTest %d: Left-aligned width\n", test_num);
//     org = printf("Printf:    |%-5c|\n", 'a');
//     ft = ft_printf("ft_printf: |%-5c|\n", 'a');
//     test_return_values(org, ft, test_num++);
//     // Edge cases
//     printf("\nTest %d: Null character\n", test_num);
//     org = printf("Printf:    |%c|\n", '\0');
//     ft = ft_printf("ft_printf: |%c|\n", '\0');
//     test_return_values(org, ft, test_num++);
//     printf("\nTest %d: Null character with width\n", test_num);
//     org = printf("Printf:    |%5c|\n", '\0');
//     ft = ft_printf("ft_printf: |%5c|\n", '\0');
//     test_return_values(org, ft, test_num++);
//     printf("\n=== TESTING %%s ===\n");
//     // %s works with width, precision, and minus flag
//     printf("\nTest %d: Basic string\n", test_num);
//     org = printf("Printf:    |%s|\n", "hello");
//     ft = ft_printf("ft_printf: |%s|\n", "hello");
//     test_return_values(org, ft, test_num++);
//     printf("\nTest %d: Width\n", test_num);
//     org = printf("Printf:    |%10s|\n", "hello");
//     ft = ft_printf("ft_printf: |%10s|\n", "hello");
//     test_return_values(org, ft, test_num++);
//     printf("\nTest %d: Left-aligned width\n", test_num);
//     org = printf("Printf:    |%-10s|\n", "hello");
//     ft = ft_printf("ft_printf: |%-10s|\n", "hello");
//     test_return_values(org, ft, test_num++);
//     printf("\nTest %d: Precision\n", test_num);
//     org = printf("Printf:    |%.3s|\n", "hello");
//     ft = ft_printf("ft_printf: |%.3s|\n", "hello");
//     test_return_values(org, ft, test_num++);
//     printf("\nTest %d: Width and precision\n", test_num);
//     org = printf("Printf:    |%10.3s|\n", "hello");
//     ft = ft_printf("ft_printf: |%10.3s|\n", "hello");
//     test_return_values(org, ft, test_num++);
//     printf("\nTest %d: Left-aligned width and precision\n", test_num);
//     org = printf("Printf:    |%-10.3s|\n", "hello");
//     ft = ft_printf("ft_printf: |%-10.3s|\n", "hello");
//     test_return_values(org, ft, test_num++);
//     // Edge cases
//     printf("\nTest %d: NULL string\n", test_num);
//     org = printf("Printf:    |%s|\n", NULL);
//     ft = ft_printf("ft_printf: |%s|\n", NULL);
//     test_return_values(org, ft, test_num++);
//     printf("\nTest %d: Empty string\n", test_num);
//     org = printf("Printf:    |%s|\n", "");
//     ft = ft_printf("ft_printf: |%s|\n", "");
//     test_return_values(org, ft, test_num++);
//     printf("\nTest %d: Zero precision\n", test_num);
//     org = printf("Printf:    |%.0s|\n", "hello");
//     ft = ft_printf("ft_printf: |%.0s|\n", "hello");
//     test_return_values(org, ft, test_num++);
//     printf("\n=== TESTING %%p ===\n");
//     // %p works with width and minus flag
//     num = 42;
//     ptr = &num;
//     null_ptr = NULL;
//     printf("\nTest %d: Basic pointer\n", test_num);
//     org = printf("Printf:    |%p|\n", ptr);
//     ft = ft_printf("ft_printf: |%p|\n", ptr);
//     test_return_values(org, ft, test_num++);
//     printf("\nTest %d: Width\n", test_num);
//     org = printf("Printf:    |%20p|\n", ptr);
//     ft = ft_printf("ft_printf: |%20p|\n", ptr);
//     test_return_values(org, ft, test_num++);
//     printf("\nTest %d: Left-aligned width\n", test_num);
//     org = printf("Printf:    |%-20p|\n", ptr);
//     ft = ft_printf("ft_printf: |%-20p|\n", ptr);
//     test_return_values(org, ft, test_num++);
//     // Edge cases
//     printf("\nTest %d: NULL pointer\n", test_num);
//     org = printf("Printf:    |%p|\n", null_ptr);
//     ft = ft_printf("ft_printf: |%p|\n", null_ptr);
//     test_return_values(org, ft, test_num++);
//     printf("\nTest %d: NULL pointer with width\n", test_num);
//     org = printf("Printf:    |%20p|\n", null_ptr);
//     ft = ft_printf("ft_printf: |%20p|\n", null_ptr);
//     test_return_values(org, ft, test_num++);
//     printf("\n=== TESTING %%d WITH ALL VALID FLAG COMBINATIONS ===\n");
//     // Basic tests without flags
//     printf("\nTest %d: Basic integer without flags\n", test_num);
//     org = printf("Printf:    |%d|\n", 42);
//     ft = ft_printf("ft_printf: |%d|\n", 42);
//     test_return_values(org, ft, test_num++);
//     // Width tests
//     printf("\nTest %d: Width only\n", test_num);
//     org = printf("Printf:    |%10d|\n", 42);
//     ft = ft_printf("ft_printf: |%10d|\n", 42);
//     test_return_values(org, ft, test_num++);
//     // Precision tests
//     printf("\nTest %d: Precision only\n", test_num);
//     org = printf("Printf:    |%.5d|\n", 42);
//     ft = ft_printf("ft_printf: |%.5d|\n", 42);
//     test_return_values(org, ft, test_num++);
//     // Width + Precision combinations
//     printf("\nTest %d: Width and precision\n", test_num);
//     org = printf("Printf:    |%10.5d|\n", 42);
//     ft = ft_printf("ft_printf: |%10.5d|\n", 42);
//     test_return_values(org, ft, test_num++);
//     // Minus flag combinations
//     printf("\nTest %d: Minus flag with width\n", test_num);
//     org = printf("Printf:    |%-10d|\n", 42);
//     ft = ft_printf("ft_printf: |%-10d|\n", 42);
//     test_return_values(org, ft, test_num++);
//     printf("\nTest %d: Minus flag with width and precision\n", test_num);
//     org = printf("Printf:    |%-10.5d|\n", 42);
//     ft = ft_printf("ft_printf: |%-10.5d|\n", 42);
//     test_return_values(org, ft, test_num++);
//     // Plus flag combinations
//     printf("\nTest %d: Plus flag only\n", test_num);
//     org = printf("Printf:    |%+d|\n", 42);
//     ft = ft_printf("ft_printf: |%+d|\n", 42);
//     test_return_values(org, ft, test_num++);
//     printf("\nTest %d: Plus flag with width\n", test_num);
//     org = printf("Printf:    |%+10d|\n", 42);
//     ft = ft_printf("ft_printf: |%+10d|\n", 42);
//     test_return_values(org, ft, test_num++);
//     printf("\nTest %d: Plus flag with precision\n", test_num);
//     org = printf("Printf:    |%+.5d|\n", 42);
//     ft = ft_printf("ft_printf: |%+.5d|\n", 42);
//     test_return_values(org, ft, test_num++);
//     printf("\nTest %d: Plus and minus flags with width\n", test_num);
//     org = printf("Printf:    |%+-10d|\n", 42);
//     ft = ft_printf("ft_printf: |%+-10d|\n", 42);
//     test_return_values(org, ft, test_num++);
//     // Space flag combinations (space is ignored when plus is present)
//     printf("\nTest %d: Space flag only\n", test_num);
//     org = printf("Printf:    |% d|\n", 42);
//     ft = ft_printf("ft_printf: |% d|\n", 42);
//     test_return_values(org, ft, test_num++);
//     printf("\nTest %d: Space flag with width\n", test_num);
//     org = printf("Printf:    |% 10d|\n", 42);
//     ft = ft_printf("ft_printf: |% 10d|\n", 42);
//     test_return_values(org, ft, test_num++);
//     printf("\nTest %d: Space flag with precision\n", test_num);
//     org = printf("Printf:    |% .5d|\n", 42);
//     ft = ft_printf("ft_printf: |% .5d|\n", 42);
//     test_return_values(org, ft, test_num++);
//     // Zero flag combinations (zero is ignored with precision or minus)
//     printf("\nTest %d: Zero flag with width\n", test_num);
//     org = printf("Printf:    |%010d|\n", 42);
//     ft = ft_printf("ft_printf: |%010d|\n", 42);
//     test_return_values(org, ft, test_num++);
//     printf("\nTest %d: Zero and plus flags with width\n", test_num);
//     org = printf("Printf:    |%+010d|\n", 42);
//     ft = ft_printf("ft_printf: |%+010d|\n", 42);
//     test_return_values(org, ft, test_num++);
//     printf("\nTest %d: Zero and space flags with width\n", test_num);
//     org = printf("Printf:    |% 010d|\n", 42);
//     ft = ft_printf("ft_printf: |% 010d|\n", 42);
//     test_return_values(org, ft, test_num++);
//     // Zero flag ignored cases
//     printf("\nTest %d: Zero flag with precision (zero should be ignored)\n",
//         test_num);
//     org = printf("Printf:    |%010.5d|\n", 42);
//     ft = ft_printf("ft_printf: |%010.5d|\n", 42);
//     test_return_values(org, ft, test_num++);
//     printf("\nTest %d: Zero flag with minus (zero should be ignored)\n",
//         test_num);
//     org = printf("Printf:    |%-010d|\n", 42);
//     ft = ft_printf("ft_printf: |%-010d|\n", 42);
//     test_return_values(org, ft, test_num++);
//     // Complex combinations
//     printf("\nTest %d: All valid flags together\n", test_num);
//     org = printf("Printf:    |%+-10.5d|\n", 42);
//     ft = ft_printf("ft_printf: |%+-10.5d|\n", 42);
//         test_return_values(org, ft, test_num++);
//     return (0);
// }
