/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:03:31 by masoares          #+#    #+#             */
/*   Updated: 2024/04/15 12:12:08 by masoares         ###   ########.fr       */
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

void	heredoc_writer(char *line_read, char ***heredocs, int i, t_localenv *local)
{
	int		n_heredocs;
	t_heredocker	heredocker;

	n_heredocs = heredoc_counter(line_read, i);
	if (n_heredocs == 0)
		return ;
	heredocker.heredocs = heredocs;
	heredocker.n_heredocs = n_heredocs;
	heredocker.line_read = line_read;
	heredocker.i = i;
	adjust_heredocs(heredocker, local);
}

int		adjust_heredocs(t_heredocker heredocker, t_localenv *local)
{
	int		k;
	int		total_heredocs;
	char	**new_heredocs;
	int		j;

	k = 0;
	j = 0;
	if (*(heredocker.heredocs))
	{
		while ((*(heredocker.heredocs))[k])
			k++;
	}
	total_heredocs = k + heredocker.n_heredocs;
	new_heredocs = (char **)malloc(sizeof(char *) * (total_heredocs + 1));
	if (new_heredocs == NULL)
		return (0);
	while (j < k)
	{
		new_heredocs[j] = (*(heredocker.heredocs))[k];
		j++;
	}
	free(*(heredocker.heredocs));
	add_heredocs(&new_heredocs, j, heredocker, local);
	*(heredocker.heredocs) = new_heredocs;
	return (1);
}

void	add_heredocs(char ***new_heredocs, int cur_heredocs, t_heredocker heredocker, t_localenv * local)
{
	int		heredoc_count;
	int 	j;
	heredoc_count = 0;
	j = heredocker.i;
	heredocker.i = 0;
	while (heredocker.line_read[heredocker.i] && heredocker.i <= j)
	{
		j = ignore_in_quotes(heredocker.line_read, j);
		if (heredocker.line_read[heredocker.i] == '<' && heredocker.i > 0 && heredocker.line_read[heredocker.i - 1] == '<')
		{
			if (heredoc_count == cur_heredocs) 
				heredocker.i = heredoc_creator(new_heredocs, &cur_heredocs, heredocker, local);
			heredoc_count++;
		}
		else
			heredocker.i++;
	}
	(*new_heredocs)[cur_heredocs] = NULL;
	return ;
}
