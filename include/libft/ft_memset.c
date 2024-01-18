/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:15:00 by masoares          #+#    #+#             */
/*   Updated: 2023/10/05 19:32:23 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <string.h>
#include <stdlib.h>

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*p;

	p = str;
	i = 0;
	while (i < n)
	{
		*(p + i) = c;
		i++;
	}
	return (str);
}
/*
int main () {
   char str[50];

   strcpy(str,"This is string.h library function");
   puts(str);

   ft_memset(str,'$',7);
   puts(str);

   return(0);
}
*/
