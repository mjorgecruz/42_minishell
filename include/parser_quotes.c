/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 12:35:14 by masoares          #+#    #+#             */
/*   Updated: 2024/02/14 13:52:37 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*This file makes the first clean-up of the string received in the terminal
It gets rid of the unnecessary quotes*/

#include "minishell.h"

bool	parser_quotes(char *input)
{
	int		i;
	int		j;

	i = 0;
	while (input[i])
	{
		if (input[i] == 34 || input[i] == 39)
		{
			j = i;
			i++;
			while (input[i] != input[j])
			{
				if (input[i] == 0)
				{
					return (false);
				}
				i++;
			}
		}
		i++;
	}
	return (true);
}
