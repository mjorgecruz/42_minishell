/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:12:32 by masoares          #+#    #+#             */
/*   Updated: 2024/01/30 14:08:21 by masoares         ###   ########.fr       */
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
	join_to_line(&total_line);
	if (total_line && *total_line)
		add_history(total_line);
	return (total_line);
}

void	join_to_line(char **total_line)
{
	char 	*line_read;
	char	*garbage;
	int		i;
	
	i = 0;
	garbage = NULL;
	line_read = NULL;
	if (*total_line[(int) ft_strlen(*total_line) -1] == '|')
	{
		ft_parser(*total_line);
		line_read = readline("> ");
		garbage = *total_line;
		*total_line = ft_strjoin(*total_line, line_read);
		free(garbage);
		while (line_read[i] == ' ' || line_read[i] == '|' || line_read[i] == '\0')
		{
			i++;
			if (!ft_strchr(line_read,'\0') && !ft_strchr(line_read,'|')
				&& !ft_strchr(line_read,' '))
			{
				garbage = *total_line;
				*total_line = ft_strjoin(*total_line, line_read);
				return ;
			}
			else
			{
				garbage = *total_line;
				*total_line = ft_strjoin(*total_line, line_read);
				line_read = readline("> ");
				i = 0;
			}
		}
	}
}

//bool ends_with_pipe