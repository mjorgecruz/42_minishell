/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:48:29 by masoares          #+#    #+#             */
/*   Updated: 2023/10/05 19:30:56 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*p;

	p = s;
	i = 0;
	if (n == 0)
		return ;
	while (i < n)
	{
		*(p + i) = '\0';
		i++;
	}
}
/*
#include <string.h>
#include <stdio.h>

int main(void)
{
	char buffer[80];
	bzero(buffer, 80);
	printf ("%s\n", buffer);
}*/
