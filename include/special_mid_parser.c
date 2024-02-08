/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_mid_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 09:45:57 by masoares          #+#    #+#             */
/*   Updated: 2024/02/08 10:55:25 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool mid_parser_iteration(char *str) //review mid parser for cases with 3
{
	int i;
	
	i = -1;
	while (str[++i])
	{
		i = ignore_in_quotes(str, i);
		if (i >= 0 && str[i])
			i = check_pipes(str, i);
		if (i >= 0 && str[i])
		{
			i = ignore_spaces(str, i);
			i = check_redirs(str, i);
		}
		if (i >= 0 && str[i])
		{
			i = ignore_spaces(str, i);
			i = check_uppersand(str, i);
		}
		if (i == -1)
			return false;
	}
	return true;
}

int check_pipes(char *str, int pos)
{
	if (str[pos] != '|')
		return (pos);
	else if (str[pos] == str[pos + 1])
	{
		pos = ignore_spaces(str, pos + 2);
		if (str[pos] == '|' || str[pos] == '&')
			return (error_definer(&str[pos]), -1);
	}
	else if (!is_special_char(str[pos + 1]))
	{
		pos = ignore_spaces(str, pos + 1);
		if (str[pos] == '|')
			return (error_definer(&str[pos]), -1);
		else if (str[pos] == '&')
			return (errors(SYNTAX_AMP, NULL), -1);
	}
	else if (is_special_char(str[pos + 1]))
	{
		pos = ignore_spaces(str, pos + 1);
		if (str[pos] == '|')
			return (error_definer(&str[pos]), -1);
		else if (str[pos] == '&')
			return (errors(SYNTAX_AMP, NULL), -1);
	}
	return (pos);
}

int check_redirs(char *str, int pos)
{
	if (str[pos] == '>' || str[pos] == '<')
	{
		if (str[pos] == str[pos + 1])
		{
			pos = pos + 2;
			if (has_valid_cmd_after(str, &pos))
				return (pos);
			pos = ignore_spaces(str, pos);
			return (error_definer(&str[pos]), -1);
		}
		else if (!is_special_char(str[pos + 1]))
		{
			pos = pos + 1;
			if (has_valid_cmd_after(str, &pos))
				return (pos);
			return (error_definer(&str[pos]), -1);
		}
		else if (str[pos] == '>' && is_special_char(str[pos + 1]))
		{
			if (str[pos + 1] == '|' || str[pos + 1] == '&')
				return (error_definer(&str[pos + 1]), -1);
			pos = ignore_spaces(str, pos + 2);
		}
		else if (str[pos] == '<' && is_special_char(str[pos + 1]))
		{
			if (str[pos + 1] == '|' || str[pos + 1] == '&')
				return (error_definer(&str[pos + 1]), -1);
			pos = ignore_spaces(str, pos + 2);
			if (!has_valid_cmd_after(str, &pos + 2))
				return (error_definer(&str[pos + 2]), -1);
		}
	}
	return (pos);
}

int check_uppersand(char *str, int pos)
{
	if (str[pos] != '&')
		return (pos);
	else if (str[pos] == '&')
	{
		if (str[pos] == str[pos + 1])
			return (pos + 2);
	}
	return (-1);
}
