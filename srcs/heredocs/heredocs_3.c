/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:29:43 by masoares          #+#    #+#             */
/*   Updated: 2024/04/12 09:30:26 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

static int	heredoc_reader(char ***new_heredocs, int *cur_heredocs, int fd);
static int	*forking_heredocs(char *final_str, char *line_read, int n_letters, int i);
static int write_to_fd(char *final_str, char *line_read,int *fd, int n_letters);

int heredoc_creator(char ***new_heredocs, int *cur_heredocs, char *line_read, int i)
{
	char	*final_str;
	int		n_letters;
	int		*fd;

	final_str = NULL;
	i = ignore_spaces(line_read, i + 1);
	n_letters = 0;
	(*new_heredocs)[*cur_heredocs] = NULL;
	if (ft_strchr("\'\"", line_read[i]))
		i++;
	fd = forking_heredocs(final_str, line_read, n_letters, i);
	heredoc_reader(new_heredocs, cur_heredocs, fd[0]);
	free(fd);
	return (i);
}

static int	*forking_heredocs(char *final_str, char *line_read, int n_letters, int i)
{
	int		pid;
	int		*fd;
	
	fd = ft_calloc(2, sizeof(int));
	// j = 0;
	n_letters = 0;
	if (ft_strchr("\'\"", line_read[i]))
		i++;
	while (!is_space(line_read[i + n_letters]) && !is_special_char(line_read[i+ n_letters])
		&& line_read[i + n_letters] != '\0' && !ft_strchr("\'\"", line_read[i + n_letters]))
		n_letters++;
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		switch_sig_default();
		write_to_fd(final_str, &line_read[i], fd, n_letters);
		exit(EXIT_SUCCESS);
	}
	switch_sig_function();
	waitpid(0, NULL, 0);
	close(fd[1]);
	return (fd);
}

static int write_to_fd(char *final_str, char *line_read,int *fd, int n_letters)
{
	char	*str;
	int		j;
	
	j = 0;
	close(fd[0]);
	str = ft_calloc(n_letters + 1, sizeof(char));
	while (j < n_letters)
	{
		str[j] = line_read[j];
		j++;
	}	
	add_partials(&(final_str), str);
	write(fd[1], final_str, ft_strlen(final_str));
	free(str);
	free(final_str);
	return (0);
}

static int	heredoc_reader(char ***new_heredocs, int *cur_heredocs, int fd)
{
	int		bread;
	char	*buffer;
	char	*temp;
		
	buffer = ft_calloc(21, sizeof(char));
	bread = read(fd, buffer, 20);
	temp = NULL;
	while (bread > 0)
	{
		temp = ft_strjoin_2(temp, buffer);
		bread = read(fd, buffer, 20);
		buffer[bread] = 0;
	}
	(*new_heredocs)[*cur_heredocs] = temp;
	(*cur_heredocs)++;
	free(buffer);
	return (0);
}
