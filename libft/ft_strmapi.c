/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 11:58:39 by masoares          #+#    #+#             */
/*   Updated: 2023/10/08 14:23:27 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
char ft_sum (unsigned int i, char c)
{
	char     out;
	out = (unsigned int)c + i;
	return ((int)out);
}*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*dest;
	unsigned int	len;
	unsigned int	i;

	i = 0;
	len = ft_strlen(s);
	dest = malloc (len + 1);
	if (dest == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		dest[i] = f(i, s[i]);
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
/*
int main (void)
{
	printf("%s\n", ft_strmapi("asde  ssas", ft_sum));
}*/
