/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:05:14 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/19 15:05:15 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i1;
	size_t	i2;
	size_t	j;
	char	*s;

	j = 0;
	i1 = ft_strlen(s1);
	i2 = ft_strlen(s2);
	s = (char *) malloc (sizeof(char) * (i1 + i2 + 1));
	if (s == NULL)
		return (NULL);
	while (j < i1)
	{
		s[j] = s1[j];
		j++;
	}
	while (j < i1 + i2)
	{
		s[j] = s2[j - i1];
		j++;
	}
	s[j] = '\0';
	return (s);
}
/*
int main (void)
{
	char	*s1;
	char	*s2;
	
	s1 = "";
	s2 = "";
	printf("%s\n", ft_strjoin(s1, s2)); 
}*/
