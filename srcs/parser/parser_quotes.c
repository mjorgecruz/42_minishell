/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 12:35:14 by masoares          #+#    #+#             */
/*   Updated: 2024/04/19 09:01:31 by luis-ffe         ###   ########.fr       */
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

void	check_next_cmd(char *str)
{
	int		pos;

	pos = 0;
	pos = ignore_spaces(str, pos);
	if (str[pos] == '\0')
		errors(SYNTAX_NEWLINE, NULL);
}

int	check_uppersand(char *str, int pos)
{
	if (str[pos] != '&')
		return (pos);
	else if (str[pos] == '&')
	{
		if (str[pos] == str[pos + 1])
			return (pos + 2);
	}
	return (errors(SYNTAX_AMP, NULL), -1);
}
