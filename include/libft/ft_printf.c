/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:10:53 by masoares          #+#    #+#             */
/*   Updated: 2023/11/10 16:15:59 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_cases(char ch, va_list list);

int	ft_printf(const char *str, ...)
{
	int		counter;
	va_list	ptr;

	counter = 0;
	va_start(ptr, str);
	while (*str != '\0')
	{
		if (*str == '%')
		{
			counter = counter + ft_cases(*(str + 1), ptr);
			str++;
		}
		else
		{
			write(1, str, 1);
			counter++;
		}
		str++;
	}
	va_end(ptr);
	return (counter);
}

int	ft_cases(char ch, va_list list)
{
	int	count;

	count = 1;
	if (ch == 'c')
		count = ft_putchar_fd(va_arg(list, int), 1);
	if (ch == 's')
		count = ft_putstr_fd(va_arg(list, char *), 1);
	if (ch == 'p')
		count = ft_putadd_fd(va_arg(list, unsigned long), 1);
	if (ch == 'd')
		count = ft_putnbr_fd(va_arg(list, int), 1);
	if (ch == 'i')
		count = ft_putnbr_fd(va_arg(list, int), 1);
	if (ch == 'u')
		count = ft_putunbr_fd(va_arg(list, unsigned int), 1, 10);
	if (ch == 'x')
		count = ft_putnbr_base_sc(va_arg(list, unsigned int), 16, ch);
	if (ch == 'X')
		count = ft_putnbr_base_sc(va_arg(list, unsigned int), 16, ch);
	if (ch == '%')
		write(1, &ch, 1);
	return (count);
}
/*
int	main(void)
{
	char	*c;

	c = "werty";
	// ft_printf("%d\n", ft_printf("Ca%calho  %s
	 %d  %i %x %X %u %p\n", 's', "casalho", -124
	 25, -12425, 123456789, 123456789, (unsigned int)123456789, c));
	// printf("%d\n", printf("Ca%calho  %s  %d  %i %x %
	X %u %p\n", 's', "casalho", -12425, -12425, 123456789,
	 123456789, (unsigned int)123456789, c));	
	// ft_printf("NULL %s\n", "");
	// printf("NULL %s\n", (char *)NULL);
	//printf("%d\n", ft_printf("123456789"));
	//ft_printf("%d\n", ft_printf("%d %d\n", -1, -9));
	//printf("%d\n", printf("%d %d\n", -1, -9));
	//ft_printf("%d\n", ft_printf("%d %d\n", INT_MAX, INT_MIN));
	//printf("%d\n", printf("%d %d\n", INT_MAX, INT_MIN));
	//ft_printf("%d\n", ft_printf("%i %i\n", INT_MAX, INT_MIN));
	//printf("%d\n",printf("%i %i\n", INT_MAX, INT_MIN));
	//ft_printf("%d\n", ft_printf("%x %X\n", UINT_MAX, UINT_MAX));
	//printf("%d\n",printf("%x %X\n", UINT_MAX, UINT_MAX));
	//ft_printf("%d\n", ft_printf("%x %X\n", -100, -100));
	//printf("%d\n",printf("%x %X\n", -100, -100));
	//ft_printf("%d\n", ft_printf("%u %u\n", UINT_MAX, -100));
	//printf("%d\n",printf("%u %u\n", UINT_MAX, -100));
	//ft_printf("%d\n", ft_printf(" %u %u %u %u i\n", LONG_MINi,
	//ULONG_MAX, 0, -42));
	//printf("%d\n",printf(" %u %u %u %u \n", LONG_MIN, ULONG_MAX, 0, -42));
	// ft_printf("%d\n", ft_printf("%p\n", -1));
	// printf("%d\n",printf("%p\n", -1));
	// ft_printf("%d\n", ft_printf("%p\n", 15));
	// printf("%d\n",printf("%p %p\n", c, NULL));
	// ft_printf("%d\n", ft_printf("%p %p\n", LONG_MIN, LONG_MAX));
	// printf("%d\n",printf("%p %p\n", LONG_MIN, LONG_MAX));
	// ft_printf("%d\n", ft_printf("%p %p\n", INT_MIN, INT_MAX));
	// printf("%d\n",printf("%p %p\n", INT_MIN, INT_MAX));
	// ft_printf("%d\n", ft_printf("%p %p\n",ULONG_MAX, -ULONG_MAX));
	// printf("%d\n",printf("%p %p\n", ULONG_MAX, -ULONG_MAX));
	return (1);
}
*/
