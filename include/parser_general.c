/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_general.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:11:05 by masoares          #+#    #+#             */
/*   Updated: 2024/01/21 00:05:49 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*This file contains the general process to clear the input received from 
the terminal*/

#include "minishell.h"

char	*ft_parser(char *line_read)
{
	char	*clean_line;

	clean_line = parser_quotes(line_read);
	free(line_read);
	clean_line = parser_special(clean_line);
	//printf("%s\n", clean_line);
	return(clean_line);
}