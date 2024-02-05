/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_special_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:14:38 by masoares          #+#    #+#             */
/*   Updated: 2024/02/01 15:45:15 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_pipe(const char* str, int pos)
{
	if (str[pos] == '|' && str[pos + 1] != '|')
	{
		pos = ignore_spaces(str, pos + 1);
		if (str[pos] != '|')
			return(true);
	}
	return (false);
}

bool find_specials_outside_quotes(const char *str)
{
	int i;

	i = -1;
	while(str[++i])
	{
		i = ignore_in_quotes(str, i);
		if	(is_special_char(str[i]))
			return (true);
	}
	return (false);
}

int	find_same_trio(const char *str, int pos)
{
	if (str[pos] && str[pos + 1] && str[pos + 2])
	{
		if(str[pos] == str[pos + 1] && str[pos + 2] == str[pos])
			return (1);
	}
	return (0);
}

int find_equal_trio_nospaces(const char *str)
{
	int i;

	i = -1;
	while(str[++i])
	{
		i = ignore_in_quotes(str, i);
		if (is_special_char(str[i]))
		{
			if (find_same_trio(str, i))
				return (1);
			i++;
				
		}
	}
	return (0);
}

bool check_invalid_specialcount(const char *str, int pos)
{
	int count;
	pos--;
	while (str[++pos])
	{
		count = 0;
		pos = ignore_in_quotes(str, pos);
		while (str[pos] && str[pos] != 39 && str[pos] != 34)
		{
			if (is_special_char(str[pos]))
			{
				count++;
				if (count > 4)
					return (true);
				
			}
			pos++;
		}
	}
	return (false);
}
