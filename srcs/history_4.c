/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:48:50 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/20 14:53:09 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	join_to_line(char **total_line, char ***heredocs, t_localenv *local)
{
	//char	*line_read;
	int		i;

	i = 0;
	//line_read = NULL;
	if (!ft_parser(*total_line, &i))
	{
		heredoc_writer(*total_line, heredocs, i, local);
		free_split(*heredocs);
		return (false);
	}
	heredoc_writer(*total_line, heredocs, i, local);
	if (!writer_from_input(total_line, heredocs, local, i))
		return (false);
	if (!ft_parser(*total_line, &i))
		return (free(total_line), false);
	return (true);
}
