/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 12:35:14 by masoares          #+#    #+#             */
/*   Updated: 2024/02/15 13:22:11 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*This file makes the first clean-up of the string received in the terminal
It gets rid of the unnecessary quotes*/

#include "../../includes/minishell.h"

bool	parser_quotes(char *input, int *i)
{
	int		j;

	if (input[*i] == '\'' || input[*i] == '\"')
	{
		j = *i;
		(*i)++;
		while (input[*i] != input[j])
		{
			if (input[*i] == 0)
			{
				if (input[j] == '\"')
					return (errors(SYNTAX_ASP, NULL), false);
				else if (input[j] == '\'')
					return (errors(SYNTAX_S_ASP, NULL), false);
			}
			(*i)++;
		}
	}
	return (true);
}
