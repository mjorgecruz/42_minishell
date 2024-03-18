/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 13:50:17 by masoares          #+#    #+#             */
/*   Updated: 2023/11/10 16:18:08 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}
/*
#include <fcntl.h>
int main (void)
{
	int     fd;
	
	fd = open("test", O_RDWR | O_TRUNC | O_CREAT, S_IRWXU);
	ft_putchar_fd('A', fd);
	close(fd);
}*/
