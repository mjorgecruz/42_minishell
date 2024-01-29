/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_general.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:11:05 by masoares          #+#    #+#             */
/*   Updated: 2024/01/29 10:36:51 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*This file contains the general process to clear the input received from 
the terminal*/

#include "minishell.h"

void	ft_parser(char *line_read)
{
	parser_quotes(line_read);
	parser_special(line_read);
	printf("%s\n", line_read);
	return ;
}
