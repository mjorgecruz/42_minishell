/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:53:10 by masoares          #+#    #+#             */
/*   Updated: 2024/04/21 14:23:57 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*add_simple_wildcard(char *str, int *i)
{
	char	*wildcard;
	int		j;

	j = *i - 1;
	while (j >= 0 && !is_special_char(str[j]))
	{
		if (str[j] == '<' && j > 0 && str[j - 1] == '<')
			return ("");
		j--;
	}
	wildcard = ft_calloc(1 + 1, sizeof(char));
	wildcard[0] = '*';
	wildcard[1] = '\0';
	return (wildcard);
}

char	*add_forw_wildcard(char *str, int *i)
{
	int		beg;
	int		end;
	char	*wildcard;
	int		j;

	beg = *i;
	(*i)++;
	while (str[*i] && !is_space(str[*i]) && !is_special_char(str[*i]))
		(*i)++;
	end = *i - 1;
	j = 0;
	wildcard = (char *) malloc(sizeof(char) * (end - beg + 2));
	while (beg <= end)
	{
		wildcard[j] = str[beg];
		beg++;
		j++;
	}
	wildcard[j] = '\0';
	return (wildcard);
}

char	*add_back_wildcard(char *str, int *i)
{
	int		beg;
	int		end;
	char	*wildcard;
	int		j;

	end = *i;
	beg = *i;
	j = *i - 1;
	while (j >= 0 && !is_special_char(str[j]))
	{
		if (str[j] == '<' && j > 0 && str[j - 1] == '<')
			return ("");
		j--;
	}
	while (beg >= 0 && !is_space(str[beg]) && !is_special_char(str[beg]))
		(beg)--;
	j = 0;
	wildcard = ft_calloc(end - beg + 2, sizeof(char));
	while (++beg <= end)
	{
		wildcard[j] = str[beg];
		j++;
	}
	return (wildcard);
}

char	*add_middle_wildcard(char *str, int *i)
{
	int		beg;
	int		end;
	char	*wildcard;
	int		j;

	j = 0;
	while (str[*i] && !is_space(str[*i]) && !is_special_char(str[*i]))
		(*i)++;
	end = *i;
	(*i)--;
	while ((*i) >= 0 && !is_space(str[*i]) && !is_special_char(str[*i]))
		(*i)--;
	beg = *i + 1;
	wildcard = (char *) malloc(sizeof(char) * (end - beg + 2));
	while (beg < end)
	{
		wildcard[j] = str[beg];
		beg++;
		j++;
	}
	wildcard[j] = '\0';
	*i = end;
	return (wildcard);
}
