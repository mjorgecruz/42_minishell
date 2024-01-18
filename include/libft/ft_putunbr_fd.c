/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 09:53:14 by masoares          #+#    #+#             */
/*   Updated: 2023/11/10 15:40:50 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putunbr(unsigned long num, int fd, int size);

int	ft_putunbr_fd(unsigned long nbr, int fd, int size)
{
	int	counter;

	counter = 0;
	if (nbr == 0)
		counter = 1;
	ft_putunbr(nbr, fd, size);
	while (nbr != 0)
	{
		nbr = nbr / size;
		counter++;
	}
	return (counter);
}

int	ft_putunbr(unsigned long num, int fd, int size)
{
	if (size == 10)
	{
		if (num <= 9)
			write (fd, &"0123456789"[num], 1);
		else
		{
			ft_putunbr(num / 10, fd, size);
			ft_putunbr(num % 10, fd, size);
		}
	}
	if (size == 16)
	{
		if (num <= 15)
			write (fd, &"0123456789abcdef"[num], 1);
		else
		{
			ft_putunbr(num / size, fd, size);
			ft_putunbr(num % size, fd, size);
		}
	}
	return (0);
}
