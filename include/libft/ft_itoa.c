/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 11:11:37 by masoares          #+#    #+#             */
/*   Updated: 2023/10/08 20:33:26 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_digits(long n)
{
	int		count;

	count = 0;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

int	ft_power(int n, int pow)
{
	int	i;
	int	num;

	num = n;
	i = 1;
	if (pow == 0)
		n = 1;
	while (i < pow)
	{
		n = n * num;
		i++;
	}
	return (n);
}

char	*write_num(long n, int d)
{
	char	*str;
	int		i;

	i = 0;
	if (n < 0)
		d++;
	str = (char *) malloc (sizeof(char) * (d + 1));
	if (str == NULL)
		return (NULL);
	if (n < 0)
	{
		i = 1;
		str[0] = '-';
		n = n * (-1);
		d--;
	}
	while (--d >= 0)
	{
		str[i++] = (n / ft_power(10, d)) + '0';
		n = n - ((n / ft_power(10, d)) * ft_power(10, d));
	}
	str[i] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	int		d;
	char	*str;
	long	num;

	num = n;
	d = count_digits(num);
	if (d == 0)
	{
		str = (char *) malloc (sizeof(char) * 2);
		if (str == NULL)
			return (NULL);
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	str = write_num(num, d);
	return (str);
}

/*
int main(void)
{
	printf("%s\n", ft_itoa(ft_atoi("-3590")));
}*/
