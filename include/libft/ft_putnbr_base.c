/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 18:25:22 by masoares          #+#    #+#             */
/*   Updated: 2023/11/10 15:39:16 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "libftprintf.h"
#include "libft.h"

int	verify_base(char *base);
int	ft_putnbr_base(unsigned int nbr, char *base, int fd);
int	number_conv(unsigned int nbr, int size, char *base, int fd);

int	ft_putnbr_base(unsigned int nbr, char *base, int fd)
{
	int		size;

	size = verify_base(base);
	number_conv(nbr, size, base, fd);
	return (ft_count_num2(nbr, 16));
}

int	verify_base(char *base)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	while (base[i] != '\0')
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
		i++;
	}
	j = 0;
	while (j <= i)
	{
		k = j + 1;
		while (k < i)
		{
			if (base[j] == base[k])
				return (0);
			k++;
		}
		j++;
	}
	return (i);
}

int	number_conv(unsigned int nbr, int size, char *base, int fd)
{
	int		num;
	char	based_num;

	if (nbr / size == 0)
	{
		num = nbr % size;
		based_num = base[num];
		write(1, &based_num, fd);
	}
	else
	{
		number_conv(nbr / size, size, base, fd);
		number_conv(nbr % size, size, base, fd);
	}
	return (0);
}

	// if (size == 0 || size == 1)
	// 	return (0) ;
	// if (nbr < 0)
	// {
	// 	write(1, "-", 1);
	// 	nbr = -nbr;
	// }