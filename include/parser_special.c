/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_special.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/02/14 13:49:04 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser_special_first_module(char *str)
{
	int		specialcount;
	
	// &i = 0;
	specialcount = -1;
	specialcount = check_invalid_specialcount(str, 0);
	if(find_specials_outside_quotes(str) == false)
		return (1);
	else if (is_invalid_start_sign(str))
		return (0);
	else if (find_equal_trio_nospaces(str))
		return (0);
	else if (specialcount >=0)
	{
		error_definer(&str[specialcount]);
		return (0);
	}
	return (1);
}

bool	parser_special_module_two(char *str)
{
	if (mid_parser_iteration(str))
		return (true);
	return false;
}

bool	parser_special(char *str)
{
	if (parser_special_first_module(str) == false)
		return (false);
	if (parser_special_module_two(str) == false)
		return (false);
	return true;
}

