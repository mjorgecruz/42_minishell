/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:51:09 by masoares          #+#    #+#             */
/*   Updated: 2023/10/08 20:12:45 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	j = ft_strlen(s1);
	while (ft_strchr(set, s1[i]) != NULL && s1[i] != '\0')
		i++;
	if (i == ft_strlen(s1))
		return (ft_strdup(""));
	while (ft_strchr(set, s1[j - 1]) != NULL && j != 0)
		j--;
	return (ft_substr(s1, i, j - i));
}
/*
int main (void)
{
	printf("%s\n", ft_strtrim("  JORGE 		", " 	"));
}*/
