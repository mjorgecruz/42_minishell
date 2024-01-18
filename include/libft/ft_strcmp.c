/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:33:38 by masoares          #+#    #+#             */
/*   Updated: 2023/11/24 15:44:01 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *str1, const char *str2)
{
	size_t			i;
	unsigned char	*n1;
	unsigned char	*n2;

	n1 = (unsigned char *)str1;
	n2 = (unsigned char *)str2;
	i = 0;
	if (ft_strlen(str1) == ft_strlen(str2))
	{
		while (n1[i] == n2[i] && i < ft_strlen(str1))
			i++;
	}
	else
		return (1);
	return (n1[i] - n2[i]);
}

/*
#include <stdio.h>
#include <string.h>

int main ()
{
	printf ("%d\n", ft_strcmp("tost\0", "test\0"));
	return (0);
}
*/