/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:31:12 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/19 10:32:28 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	wmiddle(char *str, char *comp)
{
	char	*wildcard;
	int		i;
	int		j;
	int		res;

	i = 0;
	j = 0;
	while (str[i] && str[i] == '*')
		i++;
	j = i;
	while (str[j] && str[j] != '*')
		j++;
	wildcard = ft_calloc(j - i + 1, sizeof(char));
	if (wildcard == NULL)
		return (0);
	j = 0;
	while (str[i + j] && str[i + j] != '*')
	{
		wildcard[j] = str[i + j];
		j++;
	}
	wildcard[j] = '\0';
	i = 0;
	while (comp[i])
	{
		res = mega_wildcmp(wildcard, comp, i);
		i++;
		if (res > 0)
			break;
	}
	free(wildcard);
	return (res);
}

int	wmega_back(char *str, char *comp)
{
	int		res;
	int		i;
	char	*wildcard;
	char	*prev;
	char	*letter;

	i = 0;
	res = 0;
	wildcard = NULL;
	res += wback(str, comp);
	letter = ft_calloc(2, sizeof(char));
	if (res == 0)
		return (0);
	while (str[i] != '*')
		i++;
	while (str[i])
	{
		if (str[i] != '*')
		{
			prev = wildcard;
			letter[0] = str[i];
			wildcard = ft_strjoin(prev, letter);
			if (prev != NULL)
				free(prev);
		}
		i++;
	}
	i = 0;
	while (str[i] != '*')
		i++;
	res += order_cmp(wildcard, &comp[i]);
	if (res < 2)
		return (free(wildcard), free(letter), 0);
	return(free(wildcard), free(letter), 1);
}
