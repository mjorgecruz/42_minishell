/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:03:31 by masoares          #+#    #+#             */
/*   Updated: 2024/04/13 17:09:52 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

int	heredoc_counter(char *line_read, int i)
{
	int	j;
	int	heredocs;

	heredocs = 0;
	j = 0;
	while (line_read[j] && j <= i)
	{
		j = ignore_in_quotes(line_read, j);
		if (j - 1 >= 0 && line_read[j] && line_read[j] == '<' && line_read[j - 1] == '<')
			heredocs++;
		j++;
	}
	return (heredocs);
}

void	heredoc_writer(char *line_read, char ***heredocs, int i)
{
	int		n_heredocs;

	n_heredocs = heredoc_counter(line_read, i);
	if (n_heredocs == 0)
		return ;
	adjust_heredocs(heredocs, n_heredocs, line_read, i);
}

int		adjust_heredocs(char ***heredocs, int n_heredocs, char *line_read, int i )
{
	int		k;
	int		total_heredocs;
	char	**new_heredocs;
	int		j;

	k = 0;
	j = 0;
	if (*heredocs)
	{
		while ((*heredocs)[k])
			k++;
	}
	total_heredocs = k + n_heredocs;
	new_heredocs = (char **)malloc(sizeof(char *) * (total_heredocs + 1));
	if (new_heredocs == NULL)
		return (0);
	while (j < k)
	{
		new_heredocs[j] = (*heredocs)[k];
		j++;
	}
	free(*heredocs);
	add_heredocs(&new_heredocs, j, line_read, i);
	*heredocs = new_heredocs;
	return (1);
}

void	add_heredocs(char ***new_heredocs, int cur_heredocs, char *line_read, int i)
{
	int		j;
	int		heredoc_count;

	j = 0;
	heredoc_count = 0;
	while (line_read[j] && j <= i)
	{
		j = ignore_in_quotes(line_read, j);
		if (line_read[j] == '<' && line_read[j - 1] == '<')
		{
			if (heredoc_count == cur_heredocs) 
				j = heredoc_creator(new_heredocs, &cur_heredocs, line_read, j);
			heredoc_count++;
		}
		else
			j++;
	}
	(*new_heredocs)[cur_heredocs] = NULL;
	return ;
}
