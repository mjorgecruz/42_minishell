/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:13:14 by masoares          #+#    #+#             */
/*   Updated: 2023/10/08 14:54:53 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*chb;

	chb = (char *)big;
	i = 0;
	if (*little == '\0')
		return (chb);
	while (*(big + i) != '\0' && i < len)
	{
		j = 0;
		while (*(big + i + j) == *(little + j) && i + j < len \
			&& *(big + i + j) != '\0')
			j++;
		if (*(little + j) == '\0')
			return (chb + i);
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
int main (void)
{
	const char *largestring = "Foo Bar Baz";
    const char *smallstring = "";
    char *ptr;

    ptr = ft_strnstr(largestring, smallstring, 14);
	printf("%s\n", ptr);
}
*/