/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_parenthesis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:34:59 by masoares          #+#    #+#             */
/*   Updated: 2024/02/15 10:51:18 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*This file handles the first division of commands based on the existence of parenthesis*/
#include "minishell.h"

int	parser_parenthesis(char *total_line, int *i)
{
	if (!check_operator_open_p(total_line, i))
		return (-1);
	if (!check_open_p_operator(total_line, i))
		return (-2);
	if (!check_operator_closed_p(total_line, i))
		return (-3);
	if (!check_closed_p_operator(total_line, i))
		return (-4);
	return (0);
}

bool	check_operator_open_p(char *total_line, int *i)
{
	int		k;
	int		j;
		
	k = 0;
	j = 0;
	while (total_line[k] && k <= *i)
	{
		if (total_line[k] == '(')
		{
			j = k - 1;
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
		k++;
	}
	return (true);
}

bool	check_open_p_operator(char *total_line, int *i)
{
	int		k;
	int		j;
		
	k = 0;
	j = 0;
	while (total_line[k] && k <= *i)
	{
		if (total_line[k] == '(')
		{
			j = k + 1;
			j = ignore_spaces(total_line, j);
			if (total_line[j] == '(' || !is_special_char(total_line[j]))
			{
				k++;
				continue ;
			}
			else
				return (errors(SYNTAX_OPEN_P, NULL), false);
		}
		k++;
	}
	return (true);	
}

bool	check_operator_closed_p(char *total_line, int *i)
{
	int		k;
	int		j;
		
	k = 0;
	j = 0;
	while (total_line[k] && k <= *i)
	{
		if (total_line[k] == ')')
		{
			j = k - 1;
			while (j >= -1)
			{
				if (total_line[j] == ')' || !is_special_char(total_line[j]))
					break;
				else if (total_line[j] != ' ')
					return (errors(SYNTAX_CLOSE_P, NULL), false);
				j--;
			}
		}
		k++;
	}
	return (true);
}

bool	check_closed_p_operator(char *total_line, int *i)
{
	int		k;
	int		j;
		
	k = 0;
	j = 0;
	while (total_line[k] && k <= *i)
	{
		if (total_line[k] == ')')
		{
			j = k + 1;
			j = ignore_spaces(total_line, j);
			if (!total_line[j] || total_line[j] == ')' || (total_line[j] == '&'
				&& total_line[j + 1] == '&') || (total_line[j] == '|' && total_line[j + 1] == '|'))
				break;
			else
				return (errors(SYNTAX_CLOSE_P, NULL), false);
		}
		k++;
	}
	return (true);
}
