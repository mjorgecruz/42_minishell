/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:08:39 by masoares          #+#    #+#             */
/*   Updated: 2024/04/15 13:38:58 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

int     wildcard_checker(char *str)
{
	int     i;
	int		j;

	i = 0;
	while(str[i])
	{
		i = ignore_in_quotes(str, i);
		if (str[i] == '*')
		{
			j = i - 1;
			while (j >= 0 && !is_special_char(str[j]))
			{
				if (str[j] != '<')  
					return (1);
				if (str[j] == '<' && j > 0 && str[j - 1] != '<')
					return(1);
				j--;
			}
		}
		i++;
	}
	return (0);
}

int		wildcards_counter(char *str)
{
	int		i;
	int		counter;

	i = 0;
	counter = 0;
	while (str && str[i])
	{
		i = ignore_in_quotes(str, i);
		if (str[i] == '*')
		{
			while (str[i] && !is_space(str[i]))
				i++;
			counter++;
		}
		if (str[i] != 0)
			i++;
	}
	return (counter);
}

int		order_cmp(char *wildcard, char *str)
{
	int		res;
	
	res = 0;
	if (wildcard[0] == '*')
	{
		if (wildcard[ft_strlen(wildcard) - 1] == '*')
			res = wmiddle(wildcard, &str[res]);
		else
			res = wfront(wildcard, &str[res]);
	}
	else
	{
		res = wback(wildcard, &str[res]);
	}
	return (res);
}
