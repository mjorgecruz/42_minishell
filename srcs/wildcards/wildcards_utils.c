/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:08:39 by masoares          #+#    #+#             */
/*   Updated: 2024/04/04 09:12:50 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

int     wildcard_checker(char *str)
{
	int     i;

	i = 0;
	while(str[i])
	{
		i = ignore_in_quotes(str, i);
		if (str[i] == '*')
			return (1);
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
	while (str[i])
	{
		i = ignore_in_quotes(str, i);
		if (str[i] == '*')
		{
			while (str[i] && !is_space(str[i]))
				i++;
			counter++;
		}
		i++;
	}
	return (counter);
}

int		order_cmp(char *letters, char *str)
{
	int		i;
	int 	j;

	i = 0;
	j = 0;

	while (str[i] && letters[j])
	{
		if (str[i] == letters[j])
		{
			i++;
			j++;
		}
		else
			i++;
	}
	if (!letters[j])
		return (1);
	return (0);
}
