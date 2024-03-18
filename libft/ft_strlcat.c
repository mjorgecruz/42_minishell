/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:51:06 by masoares          #+#    #+#             */
/*   Updated: 2023/10/08 11:25:18 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	char	*c;

	j = 0;
	c = (char *) src;
	i = ft_strlen(dst);
	if (size <= i)
		return (ft_strlen(c) + size);
	while (i + j < size - 1 && c[j] != '\0')
	{
		dst[i + j] = c[j];
		j++;
	}
	dst[i + j] = '\0';
	return (i + ft_strlen(c));
}
/*
#include <stdio.h>
#include <string.h>

int main()
{
    char first[] = "";
    char last[] = "123";
    int r;
    int size = 0;
    char buffer[size];

    strcpy(buffer,first);
    r = ft_strlcat(buffer,last,size);

    puts(buffer);
    printf("Value returned: %d\n",r);
    if( r > size )
        puts("String truncated");
    else
        puts("String was fully copied");

    return(0);
}*/