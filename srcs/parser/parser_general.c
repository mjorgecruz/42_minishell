/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_general.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:11:05 by masoares          #+#    #+#             */
/*   Updated: 2024/04/18 22:10:14 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*This file contains the general process to clear the input received from 
the terminal*/

#include "../../includes/minishell.h"

bool	ft_parser(char *line_read, int *i)
{
	if (!line_read || !line_read[0])
		return (true);
	if (is_invalid_start_sign(line_read))
		return (0);
	while (line_read[*i])
	{
		if (!parser_quotes(line_read, i))
			return(false);
		if (!parser_special(line_read, i))
			return(false);
		if (line_read[*i] == '\\')
			return(errors(SYNTAX_BACKSLASH, NULL), false);
		if (line_read[*i] == ';')
			return(errors(SYNTAX_COLON, NULL), false);
		if (!text_in_parenthesis(line_read, i))
			return (errors(SYNTAX_CLOSE_P, NULL), false);
		else if (parenthesis_after_command(line_read, i))
			return (errors(SYNTAX_OPEN_P, NULL), false);
		else if (parenthesis_before_command(line_read, i))
			return (errors(SYNTAX_CMD, NULL), false);
		if (parser_parenthesis(line_read, i) < 0)
			return (false);
		(*i)++;
	}	
	if (line_read[0] && open_parenthesis(line_read) < 0)
		return(errors(SYNTAX_CLOSE_P, NULL), false);
	return (true);
}

bool	text_in_parenthesis(char *line_read, int *i)
{
	int		j;
	
	j = 0;
	if (line_read[*i] == ')')
	{
		j = (*i) - 1;
		while (j >= 0 && line_read[j] == ' ')
			j--;
		if (line_read[j] == '(')
			return (false);
	}
	return (true);
}

bool	parenthesis_after_command(char *line_read, int *i)
{
	int		j;
	
	j = 0;
	if (line_read[*i] == '(')
	{
		j = (*i) - 1;
		if (j < 0 || line_read[j] == '*')
			return (false);
		while (j >= 0 && ft_strchr(" \t\n", line_read[j]))
			j--;
		if (j >= 0 && line_read[j] != '|' && line_read[j] != '&'
			&& line_read[j] != '<' && line_read[j] != '>'&& line_read[j] != '(' )
			return (true);
	}
	if (line_read[*i] == '\0')
		return (false);
	return (false);
}

bool	parenthesis_before_command(char *line_read, int *i)
{
	int		j;

	j = 0;
	if (line_read[*i] == ')')
	{
		j = (*i) + 1;
		while (line_read[j] != '\0' && line_read[j] == ' ')
			j++;
		if (line_read[j] != '|' && line_read[j] != '&'
			&& line_read[j] != '<' && line_read[j] != '>' 
			&& line_read[j] != '\0' && line_read[j] != ')' )
			return (true);
	}
	return (false);
}
