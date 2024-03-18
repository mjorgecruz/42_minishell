/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 20:47:51 by masoares          #+#    #+#             */
/*   Updated: 2023/10/08 13:36:47 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	char	*c;

	c = (char *) src;
	i = 0;
	if (ft_strlen(c) == 0)
	{
		dst[i] = '\0';
		return (ft_strlen(c));
	}
	if (size > 0)
	{
		while (i <= ft_strlen(c) - 1)
		{
			if (i == size - 1)
				break ;
			dst[i] = c[i];
			i++;
		}
	}
	else
		return (ft_strlen(c));
	dst[i] = '\0';
	return (ft_strlen(c));
}
/*
#include <stdio.h>
void test(int size)
{
    char string[] = "Hello there, Venus";
    char buffer[19];
    int r;

    r = ft_strlcpy(buffer,string,size);

    printf("Copied '%s' into '%s', length %d\n",
            string,
            buffer,
            r
          );
}

int main()
{
    test(19);
    test(10);
    test(1);
    test(0);

    return(0);
}
*/
