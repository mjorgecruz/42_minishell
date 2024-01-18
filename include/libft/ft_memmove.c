/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 19:59:37 by masoares          #+#    #+#             */
/*   Updated: 2023/10/08 20:03:41 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove_rev(void *dest, const void *src, size_t n)
{
	const char		*s;
	unsigned int	i;
	char			*d;

	s = src;
	d = dest;
	i = n - 1;
	while (i >= 0)
	{
		*(d + i) = *(s + i);
		if (i == 0)
			break ;
		i--;
	}
	return (d);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const char		*s;
	unsigned int	i;
	char			*d;

	s = src;
	d = dest;
	i = 0;
	if (src == NULL && dest == NULL)
		return (NULL);
	if (n == 0)
		return (d);
	if (s > d)
	{
		while (i < n)
		{
			*(d + i) = *(s + i);
			i++;
		}
	}
	else if (s < d)
		d = ft_memmove_rev(dest, src, n);
	return (d);
}
/*
int main ()
{
  char str[] = "memmove can be very useful......";
  ft_memmove (str+20,str+15,0);
  puts (str);
  return 0;
}*/
