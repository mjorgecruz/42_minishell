/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_general_divider.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:34:59 by masoares          #+#    #+#             */
/*   Updated: 2024/02/13 17:06:43 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*This file handles the first division of commands based on the existence of parenthesis*/
#include "minishell.h"

int	first_general_divider(char *total_line)
{
	if (!check_operator_open_p(total_line))
		return (-1);
	if (!check_closed_p_operator(total_line))
		return (-2);		
}

bool	operator_open_p(char *total_line)
{
	
}