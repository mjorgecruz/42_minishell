/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 14:19:44 by masoares          #+#    #+#             */
/*   Updated: 2023/11/10 18:26:35 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	size_t		size;

	size = ft_strlen(s);
	write(fd, s, size);
	return ((int)size);
}
/*
#include <fcntl.h>
int main (void)
{
	int     fd;
	
	fd = open("test", O_RDWR | O_TRUNC | O_CREAT, S_IRWXU);
	ft_putstr_fd("animal", fd);
	close(fd);
}
*/