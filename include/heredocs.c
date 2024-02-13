/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:03:31 by masoares          #+#    #+#             */
/*   Updated: 2024/02/13 14:34:58 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_counter(char *line_read)
{
	int	i;
	int	heredocs;

	heredocs = 0;
	i = 0;
	while (line_read[i])
	{
		if (line_read[i] == '<' && line_read[i - 1] == '<')
			heredocs++;
		i++;
	}
	return (heredocs);
}

void	heredoc_writer(char *line_read, char ***heredocs)
{
	int		n_heredocs;

	n_heredocs = heredoc_counter(line_read);
	if (n_heredocs == 0)
		return ;
	adjust_heredocs(heredocs, n_heredocs, line_read);
}

int		adjust_heredocs(char ***heredocs, int n_heredocs, char *line_read)
{
	int		i;
	int		total_heredocs;
	char	**new_heredocs;
	int		j;
	
	i = 0;
	j = 0;
	if (*heredocs)
	{
		while ((*heredocs)[i])
			i++;
	}
	total_heredocs = i + n_heredocs;
	new_heredocs = (char **)malloc(sizeof(char *) * (total_heredocs + 1));
	if (new_heredocs == NULL)
		return (0);
	while(j < i)
	{
		new_heredocs[j] = (*heredocs)[j];
		j++;
	}
	free(*heredocs);
	add_heredocs(&new_heredocs, j, line_read);
	*heredocs = new_heredocs;
	return (1);
}

void	add_heredocs(char ***new_heredocs, int cur_heredocs, char *line_read)
{
	int		i;

	i = 0;
	while (line_read[i])
	{
		if (line_read[i] == '<' && line_read[i - 1] == '<')
		{
			i = heredoc_creator (new_heredocs, &cur_heredocs, line_read, i);
		}
		else
			i++;
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
	while (line_read[i + n_letters] != ' ' && !is_special_char(line_read[i])
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
