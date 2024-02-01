/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_general.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:11:05 by masoares          #+#    #+#             */
/*   Updated: 2024/02/01 10:24:14 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*This file contains the general process to clear the input received from 
the terminal*/

#include "minishell.h"

void	ft_parser(char *line_read)
{
	parser_quotes(line_read);
	parser_special(line_read);
	if (!text_in_parenthesis(line_read) || parenthesis_after_command(line_read)
	|| parenthesis_before_command(line_read))
		return (errors(1));
	return ;
}

bool	text_in_parenthesis(char *line_read)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line_read[i] != '\0')
	{
		pass_quotes(line_read, &i);
		if (line_read[i] == ')')
		{
			j = i - 1;
			while (j >= 0 && line_read[j] == ' ')
				j--;
			if (line_read[j] == '(')
				return (false);
		}
		i++;
	}
	return (true);
}

bool	parenthesis_after_command(char *line_read)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line_read[i] != '\0')
	{
		pass_quotes(line_read, &i);
		if (line_read[i] == '(')
		{
			if (i == 0)
				j = 0;
			else
				j = i - 1;
			while (j >= 0 && line_read[j] == ' ')
				j--;
			if (line_read[j] != '|' && line_read[j] != '&'
				&& line_read[j] != '<' && line_read[j] != '>' && j != 0)
				return (true);
		}
		i++;
	}
	if (line_read[i] == '\0')
		return (false);
	return (true);
}

bool	parenthesis_before_command(char *line_read)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line_read[i] != '\0')
	{
		pass_quotes(line_read, &i);
		if (line_read[i] == ')')
		{
			j = i + 1;
			while (line_read[j] != '\0' && line_read[j] == ' ')
				j++;
			if (line_read[j] != '|' && line_read[j] != '&'
				&& line_read[j] != '<' && line_read[j] != '>' 
				&& line_read[j] != '\0')
				return (true);
		}
		i++;
	}
	if (line_read[i] == '\0')
		return (false);
	return (true);
}