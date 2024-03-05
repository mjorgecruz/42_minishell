/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_mid_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 00:09:57 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/03/05 00:10:15 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

bool mid_parser_iteration(char *str, int *i)
{
	int		j;
	
	j = 0;
	while (str[j] && j <= *i)
	{
		j = ignore_in_quotes(str, j);
		if (j >= 0 && str[j])
			j = check_pipes(str, j);
		if (j >= 0 && str[j])
		{
			j = ignore_spaces(str, j);
			j = check_redirs(str, j);
		}
		if (j >= 0 && str[j])
		{
			j = ignore_spaces(str, j);
			j = check_uppersand(str, j);
		}
		if (j == -1)
			return false;
		if (!str[j])
			break;
		j++;
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
		if (!str[pos + 1])
			return (error_definer(&str[pos + 1]), -1);
		if (str[pos + 1] && str[pos] == str[pos + 1])
		{
			pos = ignore_spaces(str, pos + 2);
			if (has_valid_cmd_after(str, pos))
				return (pos);
			return (error_definer(&str[pos]), -1);
		}
		else if (!is_special_char(str[pos + 1]))
		{
			pos = ignore_spaces(str, pos + 2);
			if (has_valid_cmd_after(str, pos))
				return (pos);
			return (error_definer(&str[pos]), -1);
		}
		else if (str[pos + 1] && str[pos] == '>' && is_special_char(str[pos + 1]))
			pos = check_redirs_rr_sc(str, pos);
		else if (str[pos + 1] && str[pos] == '<' && is_special_char(str[pos + 1]))
			pos = check_redirs_lr_sc(str, pos);
	}
	return (pos);
}

int check_redirs_rr_sc(char *str, int pos)
{
	if (str[pos + 1] == '|' || str[pos + 1] == '&')
	{
		pos = ignore_spaces(str, pos + 2);
		if (str[pos] == '\0')
			return (errors(SYNTAX_NEWLINE, NULL), -1);
		else if (is_special_char(str[pos]))
			return (error_definer(&str[pos]), -1);
	}
	if (str[pos + 1] == '<' )
		return (errors(SYNTAX_L_S_REDIR, NULL), -1);
	pos = ignore_spaces(str, pos + 2);
	if (str[pos] == '\0')
		return (errors(SYNTAX_NEWLINE, NULL), -1);
	return (pos);
}

int check_redirs_lr_sc(char * str, int pos)
{
	if (str[pos + 1] == '|' && str[pos + 2] != '|' && str[pos + 2] != '&')
		return (errors(SYNTAX_PIPE, NULL), -1);
	else if  (str[pos + 1] == '|' && str[pos + 2] == '|')
		return (errors(SYNTAX_D_PIPE, NULL), -1);
	else if  (str[pos + 1] == '|' && str[pos + 2] == '&')
		return (errors(SYNTAX_PIPE_AMP, NULL), -1);
	else if (str[pos + 1] == '&' && str[pos + 2] != '|')
	{
		pos = ignore_spaces(str, pos + 2);		
		return (errors(SYNTAX_AMP, NULL), -1);
	}
	else if (str[pos + 1] == '&' && str[pos + 2] == '|')
		return (errors(SYNTAX_PIPE, NULL), -1);
	pos = ignore_spaces(str, pos + 2);
	if (!has_valid_cmd_after(str, pos))
		return (error_definer(&str[pos]), -1);
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
	return (errors(SYNTAX_AMP, NULL), -1);
}
