/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_special.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:55:31 by masoares          #+#    #+#             */
/*   Updated: 2024/04/19 09:02:19 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parser_special_first_module(char *str, int *i)
{
	int		specialcount;

	specialcount = -1;
	specialcount = check_invalid_specialcount(str, 0, i);
	if (find_equal_trio_nospaces(str, i))
		return (0);
	else if (specialcount >= 0)
	{
		error_definer(&str[specialcount]);
		return (0);
	}
	return (1);
}

bool	parser_special_module_two(char *str, int *i)
{
	if (mid_parser_iteration(str, i))
		return (true);
	return (false);
}

bool	parser_special(char *str, int *i)
{
	if (parser_special_first_module(str, i) == false)
		return (false);
	if (parser_special_module_two(str, i) == false)
		return (false);
	return (true);
}

bool	start_sign_pipe(char *str, int i)
{
	if (str[i] == str[i + 1])
		error_definer(&str[i]);
	else
		errors(SYNTAX_PIPE, NULL);
	return (true);
}

bool	pipe_is_first(char *s, int pos)
{
	pos = ignore_spaces(s, pos);
	if (s[pos] == '|')
	{
		return (true);
	}
	return (false);
}
