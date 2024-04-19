/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils6.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:31:39 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/19 11:53:35 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
				continue;
			else
				wild_splitter_sel(wild, j, str, &i);
			j++;
		}
		if(str[i])
			i++;
	}
	wild[j] = NULL;
	return (wild);
}

static void	wild_splitter_sel(char **wild, int j, char *str, int *i)
{
	if(((*i) == 0 || is_space(str[(*i) - 1]) || is_special_char(str[(*i) - 1]))
		&& (!str[(*i) + 1] || is_space(str[(*i) + 1])
		|| is_special_char(str[(*i) + 1])))
		wild[j] = add_simple_wildcard(str, i);
	else if (((*i) == 0 || is_space(str[(*i) - 1]) 
		|| is_special_char(str[(*i) - 1])) && (str[(*i) + 1] 
		&& !is_space(str[(*i) + 1]) && !is_special_char(str[(*i) + 1])))
		wild[j] = add_forw_wildcard(str, i);
	else if (((*i) != 0 && !is_space(str[(*i)- 1])
		&& !is_special_char(str[(*i) - 1])) && (is_space(str[(*i) + 1])
		|| is_special_char(str[(*i) + 1]) || !str[(*i) + 1]))
		wild[j] = add_back_wildcard(str, i);
	else if (!is_space(str[(*i) - 1]) && !is_special_char(str[(*i) - 1])
		&& !is_space(str[(*i) + 1]) && !is_special_char(str[(*i) + 1]))
		wild[j] = add_middle_wildcard(str, i);
}
