/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 23:25:24 by masoares          #+#    #+#             */
/*   Updated: 2024/04/09 13:57:28 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

void	add_partials(char **heredoc, char *str)
{
	char	*heredoc_line;
	
	heredoc_line = readline("> ");
	if (heredoc_line == NULL)
	{
		*heredoc = ft_calloc(1, sizeof(char));
		return (errors(HEREDOC_EOF, str));
	}
	while (ft_strcmp(str, heredoc_line))
	{
		add_newline_line(heredoc, heredoc_line);
		heredoc_line = readline("> ");
		if (heredoc_line == NULL)
			return (errors(HEREDOC_EOF, str));
	}
	if (!*heredoc)
	{
		*heredoc = ft_calloc(2, sizeof(char));
		*heredoc[0] = '\n';
	}	
	else
		*heredoc = ft_strjoin(*heredoc, "\n");
}