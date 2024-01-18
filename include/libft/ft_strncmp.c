/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:33:38 by masoares          #+#    #+#             */
/*   Updated: 2023/10/08 10:47:52 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t num)
{
	size_t			i;
	unsigned char	*n1;
	unsigned char	*n2;

	n1 = (unsigned char *)str1;
	n2 = (unsigned char *)str2;
	i = 0;
	if (num == 0)
		return (0);
	while (n1[i] == n2[i] && i < ft_strlen(str1) && i < ft_strlen(str2) \
			&& i < num - 1)
	{
		i++;
	}
	return (n1[i] - n2[i]);
}
/*
#include <stdio.h>
#include <string.h>

int main ()
{
	printf ("%d\n", ft_strncmp ("test\200", "test\0", 6));
	return 0;
}*/
