/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_parenthesis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:34:59 by masoares          #+#    #+#             */
/*   Updated: 2024/02/14 13:14:28 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*This file handles the first division of commands based on the existence of parenthesis*/
#include "minishell.h"

int	parser_parenthesis(char *total_line)
{
	if (!check_operator_open_p(total_line))
		return (-1);
	if (!check_open_p_operator(total_line))
		return (-2);
	if (!check_operator_closed_p(total_line))
		return (-3);
	if (!check_closed_p_operator(total_line))
		return (-4);
	return (0);
}

bool	check_operator_open_p(char *total_line)
{
	int		i;
	int		j;
		
	i = 0;
	j = 0;
	while (total_line[i])
	{
		if (total_line[i] == '(')
		{
			j = i - 1;
			while (total_line[j])
			{
				if (j == -1 || total_line[j] == '(' || (total_line[j] == '&'
				&& total_line[j - 1] == '&') || (total_line[j] == '|' && total_line[j - 1] == '|'))
					break;
				else if (total_line[j] != '&' && total_line[j] != '|' && total_line[j] != '(' && total_line[j] != ' ')
					return (errors(SYNTAX_OPEN_P, NULL), false);
				j--;
			}
		}
		i++;
	}
	return (true);
}

bool	check_open_p_operator(char *total_line)
{
	int		i;
	int		j;
		
	i = 0;
	j = 0;
	while (total_line[i])
	{
		if (total_line[i] == '(')
		{
			j = i + 1;
			j = ignore_spaces(total_line, j);
			if (total_line[j] == '(' || !is_special_char(total_line[j]))
			{
				i++;
				continue ;
			}
			else
				return (errors(SYNTAX_OPEN_P, NULL), false);
		}
		i++;
	}
	return (true);	
}

bool	check_operator_closed_p(char *total_line)
{
	int		i;
	int		j;
		
	i = 0;
	j = 0;
	while (total_line[i])
	{
		if (total_line[i] == ')')
		{
			j = i - 1;
			while (j >= -1)
			{
				if (total_line[j] == ')' || !is_special_char(total_line[j]))
					break;
				else if (total_line[j] != ' ')
					return (errors(SYNTAX_CLOSE_P, NULL), false);
				j--;
			}
		}
		i++;
	}
	return (true);
}

bool	check_closed_p_operator(char *total_line)
{
	int		i;
	int		j;
		
	i = 0;
	j = 0;
	while (total_line[i])
	{
		if (total_line[i] == ')')
		{
			j = i + 1;
			j = ignore_spaces(total_line, j);
			if (!total_line[j] || total_line[j] == ')' || (total_line[j] == '&'
				&& total_line[j + 1] == '&') || (total_line[j] == '|' && total_line[j + 1] == '|'))
				break;
			else
				return (errors(SYNTAX_CLOSE_P, NULL), false);
		}
		i++;
	}
	return (true);
}
