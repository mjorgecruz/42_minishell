/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:31:12 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/19 11:52:35 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int  ft_iterator(char *str, int i)
{
	while (str[i] && str[i] == '*')
		i++;
        return (i);
}

int	wmiddle(char *str, char *comp)
{
	char	*wildcard;
	int		i;
	int		j;
	int		res;

    i = ft_iterator(str, 0);
	j = i;
    j = ft_iterator(str, j);
	wildcard = ft_calloc(j - i + 1, sizeof(char));
	if (wildcard == NULL)
		return (0);
	j = -1;
	while (str[++j + i] && str[i + j] != '*')
		wildcard[j] = str[i + j];
	wildcard[j] = '\0';
	i = -1;
	while (comp[++i])
	{
		res = mega_wildcmp(wildcard, comp, i);
		if (res > 0)
			break;
	}
	free(wildcard);
	return (res);
}
