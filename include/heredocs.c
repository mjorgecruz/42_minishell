/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:03:31 by masoares          #+#    #+#             */
/*   Updated: 2024/02/15 16:08:53 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_counter(char *line_read, int i)
{
	int	j;
	int	heredocs;

	heredocs = 0;
	j = 0;
	while (line_read[j] && j <= i)
	{
		if (j - 1 >= 0 && line_read[j] == '<' && line_read[j - 1] == '<')
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
int heredoc_creator(char ***new_heredocs, int *cur_heredocs, char *line_read, int i)
{
	char	*str;
	int		n_letters;
	int		j;
	
	i = ignore_spaces(line_read, i + 1);
	n_letters = 0;
	while (line_read[i + n_letters] != ' ' && !is_special_char(line_read[i+ n_letters])
		&& line_read[i + n_letters] != '\0')
		n_letters++;
	str = ft_calloc(n_letters + 1, sizeof(char));
	j = 0;
	while (j < n_letters)
		str[j++] = line_read[i++];
	(*new_heredocs)[*cur_heredocs] = NULL;
	add_partials(&((*new_heredocs)[*cur_heredocs]), str);
	(*cur_heredocs)++;
	free(str);
	return (i);
}

void	add_newline_line(char **total_line, char *line_read)
{
	char *garbage;
	
	garbage = *total_line;
	if (*total_line != NULL)
	{
		*total_line = ft_strjoin(*total_line, "\n");
		free(garbage);
		garbage = *total_line;
		*total_line = ft_strjoin(*total_line, line_read);
		free(garbage);
	}
	else
		*total_line = line_read;
}

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
