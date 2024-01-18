/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putadd_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 11:20:50 by masoares          #+#    #+#             */
/*   Updated: 2023/11/10 15:40:48 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putadd_fd(unsigned long num, int fd)
{
	if (num == 0)
	{
		write(fd, "(nil)", 5);
		return (5);
	}
	write(fd, "0x", 2);
	return (ft_putunbr_fd(num, fd, 16) + 2);
}
