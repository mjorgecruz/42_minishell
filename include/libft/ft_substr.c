/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:10:31 by masoares          #+#    #+#             */
/*   Updated: 2023/10/08 20:42:28 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*dest;
	size_t			i;
	size_t			j;

	j = (size_t) start;
	if (ft_strlen(s) == 0)
		return (ft_strdup(""));
	if (len + j > ft_strlen(s))
	{
		if (ft_strlen(s) > j)
			len = ft_strlen(s) - j;
		else
			return (ft_strdup(""));
	}
	i = 0;
	dest = (char *) malloc (sizeof(char) * (len + 1));
	if (dest == NULL)
		return (NULL);
	while (i < len)
	{
		dest[i] = s[j + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
/*
int main (void)
{
	char	*s;

	s = "";
	printf("%s\n", ft_substr(s, 1, 0));
}*/
