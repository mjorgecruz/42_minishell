/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:03:31 by masoares          #+#    #+#             */
/*   Updated: 2024/04/08 12:59:42 by masoares         ###   ########.fr       */
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
int heredoc_creator(char ***new_heredocs, int *cur_heredocs, char *line_read, int i)
{
	char	*str;
	char	*final_str;
	int		n_letters;
	int		j;
	int		fd[2];
	int		pid;
	int		bread;
	char	*buffer;
	char	*temp;

	final_str = NULL;
	bread = 0;
	i = ignore_spaces(line_read, i + 1);
	n_letters = 0;
	while (line_read[i + n_letters] != ' ' && !is_special_char(line_read[i+ n_letters])
		&& line_read[i + n_letters] != '\0' && !ft_strchr("\'\"", line_read[i + n_letters]))
		n_letters++;
	(*new_heredocs)[*cur_heredocs] = NULL;
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		switch_sig_default();
		close(fd[0]);
		str = ft_calloc(n_letters + 1, sizeof(char));
		j = 0;
		while (j < n_letters)
			str[j++] = line_read[i++];
		add_partials(&(final_str), str);
		write(fd[1], final_str, ft_strlen(final_str));
		free(str);
		free(final_str);
		exit(EXIT_SUCCESS);
	}
	switch_sig_function();
	waitpid(0, NULL, 0);
	close(fd[1]);
	buffer = ft_calloc(21, sizeof(char));
	bread = read(fd[0], buffer, 20);
	temp = ft_strdup("");
	while (bread > 0)
	{
		temp = ft_strjoin_2(temp, buffer);
		bread = read(fd[0], buffer, 20);
		buffer[bread] = 0;
	}
	(*new_heredocs)[*cur_heredocs] = temp;
	(*cur_heredocs)++;
	free(buffer);
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
char	*ft_strjoin_2(char *s1, char const *s2)
{
	size_t	i1;
	size_t	i2;
	size_t	j;
	char	*s;

	j = 0;
	i1 = ft_strlen(s1);
	i2 = ft_strlen(s2);
	s = (char *) malloc (sizeof(char) * (i1 + i2 + 1));
	if (s == NULL)
		return (NULL);
	while (j < i1)
	{
		s[j] = s1[j];
		j++;
	}
	while (j < i1 + i2)
	{
		s[j] = s2[j - i1];
		j++;
	}
	s[j] = '\0';
	return (free(s1), s);
}
