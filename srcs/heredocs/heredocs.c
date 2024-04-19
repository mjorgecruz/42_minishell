/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 08:15:30 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/19 08:25:19 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (j - 1 >= 0 && line_read[j] && \
			line_read[j] == '<' && line_read[j - 1] == '<')
			heredocs++;
		j++;
	}
	return (heredocs);
}

void	heredoc_writer(char *line_r, char ***hdocs, int i, t_localenv *local)
{
	int				n_heredocs;
	t_heredocker	heredocker;

	n_heredocs = heredoc_counter(line_r, i);
	if (n_heredocs == 0)
		return ;
	heredocker.heredocs = hdocs;
	heredocker.n_heredocs = n_heredocs;
	heredocker.line_read = line_r;
	heredocker.i = i;
	adjust_heredocs(heredocker, local);
}

int	adjust_heredocs(t_heredocker heredocker, t_localenv *local)
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

void	add_heredocs(char ***new_hd, int cur_hd, \
t_heredocker hdoker, t_localenv *local)
{
	int		heredoc_count;
	int		j;

	heredoc_count = 0;
	j = hdoker.i;
	hdoker.i = 0;
	while (hdoker.line_read[hdoker.i] && hdoker.i <= j)
	{
		j = ignore_in_quotes(hdoker.line_read, j);
		if (hdoker.line_read[hdoker.i] == '<' && \
			hdoker.i > 0 && hdoker.line_read[hdoker.i - 1] == '<')
		{
			if (heredoc_count == cur_hd)
				hdoker.i = heredoc_creator(new_hd, &cur_hd, hdoker, local);
			heredoc_count++;
		}
		else
			hdoker.i++;
	}
	(*new_hd)[cur_hd] = NULL;
	return ;
}
