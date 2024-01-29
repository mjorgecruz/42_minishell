/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:12:32 by masoares          #+#    #+#             */
/*   Updated: 2024/01/29 16:40:49 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*This file contains functions related to the history of the terminal*/

#include "minishell.h"

char	*get_line(char *total_line)
{
	char	*line_read;
	char	*vai_fora;
	
	vai_fora = NULL;
	line_read = readline("minishell > ");
	total_line = line_read;
	while (line_read[(int) ft_strlen(line_read) -1] == '|')
	{
		line_read = readline("> ");
		vai_fora = total_line;
		total_line = ft_strjoin(total_line, line_read);
		free(vai_fora);
	}
	total_line = ft_strjoin(total_line, line_read);
	if (total_line && *total_line)
		add_history(total_line);
	return (line_read);
}

