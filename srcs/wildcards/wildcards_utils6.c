/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils6.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:31:39 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/21 14:32:31 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	wild_splitter_sel(char **wild, int j, char *str, int *i);

char	**wild_splitter(char *str, int i, int j, int k)
{
	char	**wild;

	wild = (char **) malloc (sizeof(char *) * (wildcards_counter(str) + 1));
	while (str[i])
	{
		i = ignore_in_quotes(str, i);
		if (str[i] == '*')
		{
			k = i - 1 + 1;
			while (--k >= 0 && !is_special_char(str[k]))
			{
				if (str[k] == '<' && k > 0 && str[k - 1] == '<')
					k = -10;
			}
			if (k < -5)
				continue ;
			else
				wild_splitter_sel(wild, j, str, &i);
			j++;
		}
		if (str[i])
			i++;
	}
	wild[j] = NULL;
	return (wild);
}

static void	wild_splitter_sel(char **wild, int j, char *str, int *i)
{
	if (((*i) == 0 || is_space(str[(*i) - 1]) || is_special_char(str[(*i) - 1]))
		&& (!str[(*i) + 1] || is_space(str[(*i) + 1]) || \
		is_special_char(str[(*i) + 1])))
		wild[j] = add_simple_wildcard(str, i);
	else if (((*i) == 0 || is_space(str[(*i) - 1]) || \
		is_special_char(str[(*i) - 1])) && (str[(*i) + 1] && \
		!is_space(str[(*i) + 1]) && !is_special_char(str[(*i) + 1])))
		wild[j] = add_forw_wildcard(str, i);
	else if (((*i) != 0 && !is_space(str[(*i) - 1]) && \
		!is_special_char(str[(*i) - 1])) && (is_space(str[(*i) + 1]) || \
		is_special_char(str[(*i) + 1]) || !str[(*i) + 1]))
		wild[j] = add_back_wildcard(str, i);
	else if (!is_space(str[(*i) - 1]) && !is_special_char(str[(*i) - 1])
		&& !is_space(str[(*i) + 1]) && !is_special_char(str[(*i) + 1]))
		wild[j] = add_middle_wildcard(str, i);
}

int	rewriter(char **final, char *wild, char *new, int *j)
{
	int	k;

	k = 0;
	if (new[0] == 0)
	{
		k = ft_strlcat(*final, wild, ft_strlen(*final) + ft_strlen(wild) + 2);
		(*j) += (ft_strlen(wild));
	}
	else if (new != NULL)
	{
		k = ft_strlcat(*final, new, ft_strlen(*final) + ft_strlen(new) + 2);
		(*j) += (ft_strlen(wild));
	}
	return (k);
}

void	wildcard_formatter(char **wildcard, char *str, int *i)
{
	char	*letter;
	char	*prev;

	prev = NULL;
	letter = ft_calloc(2, sizeof(char));
	while (str[*i] && str[*i] != '*')
	{
		prev = *wildcard;
		letter[0] = str[*i];
		*wildcard = ft_strjoin(prev, letter);
		free(prev);
		(*i)++;
	}
	if (str[*i] == '*')
	{
		prev = *wildcard;
		letter[0] = str[*i];
		*wildcard = ft_strjoin(prev, letter);
		free(prev);
		(*i)++;
	}
	free(letter);
}
