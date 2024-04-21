/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils7.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:11:04 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/21 14:16:53 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_wildcard(char **wild, char *origin)
{
	char	*trav;

	if (*wild == NULL)
	{
		*wild = ft_strcpy(origin);
		return ;
	}
	trav = *wild;
	*wild = ft_strjoin(*wild, " ");
	free(trav);
	trav = *wild;
	*wild = ft_strjoin(*wild, origin);
	free(trav);
}

int	free_wild_split(char **splitted)
{
	int	i;

	i = 0;
	while (splitted[i])
	{
		free(splitted[i]);
		i++;
	}
	free(splitted);
	return (0);
}

int	*check_wild_redirs(char *str, char **wild, char **new)
{
	int	i;
	int	j;
	int	k;
	int	*decider;

	i = 0;
	j = 0;
	k = 0;
	while (new[i])
		i++;
	decider = (int *)malloc(sizeof(int) * i);
	i = 0;
	while (new[i] || str[j])
	{
		if (wild[i] && mega_wildcmp(wild[i], str, j))
		{
			k = j;
			k--;
			decider[i] = decidings(str, k, new[i]);
			i++;
		}
		j++;
	}
	return (decider);
}

int	decidings(char *str, int k, char *new)
{
	int	decider;

	decider = 0;
	while (k >= 0 && is_space(str[k]))
		k--;
	if (k == -1 || (str[k] != '<' && str[k] != '>'))
		decider = 0;
	else if (str[k] == '<' && str[k - 1] == '<')
		decider = 1;
	else if (str[k] == '<')
	{
		if (wild_words(new) > 1)
			decider = -1;
	}
	else if (str[k] == '>')
	{
		if (wild_words(new) > 1)
			decider = -2;
	}
	return (decider);
}

int	wild_words(char *s)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (is_space(s[i]))
			i++;
		if (s[i] != '\0')
			count++;
		while (!is_space(s[i]) && s[i] != '\0')
		{
			i++;
		}
	}
	return (count);
}
