/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:30:40 by masoares          #+#    #+#             */
/*   Updated: 2023/11/13 10:58:33 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_words(char const *s, char c)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c) 
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**words;

	i = 0;
	words = (char **) malloc (sizeof(char *) * (count_words (s, c) + 1));
	if (words == NULL)
		return (NULL);
	while (*s)
	{
		if (*s != c && *s)
		{
			if (!ft_strchr(s, c))
				j = ft_strlen(s);
			else
				j = ft_strchr(s, c) - s;
			words[i++] = ft_substr(s, 0, j);
			s = s + j;
		}
		while (*s == c && *s)
			s++;
	}
	words[i] = NULL;
	return (words);
}
/*
int main (void)
{
	char	**words;
	int	i;
	
	i = 0;
	words = ft_split("", 'z');
	while (words[i] != NULL)
	{
		printf("%s\n", words[i]);
		i++;
	}
}*/
