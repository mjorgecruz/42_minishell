/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:29:43 by masoares          #+#    #+#             */
/*   Updated: 2024/04/13 19:40:19 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

static int	heredoc_reader(char ***new_heredocs, int *cur_heredocs, int fd);
static int	*forking_heredocs(char *final_str, t_heredocker heredocker, int n_letters, t_localenv *local);
static int write_to_fd(char *final_str, char *line_read,int *fd, int n_letters);

int heredoc_creator(char ***new_heredocs, int *cur_heredocs, t_heredocker heredocker, t_localenv *local)
{
	char	*final_str;
	int		n_letters;
	int		*fd;
	(void)	local;

	final_str = NULL;
	heredocker.i = ignore_spaces(heredocker.line_read, heredocker.i + 1);
	n_letters = 0;
	(*new_heredocs)[*cur_heredocs] = NULL;
	if (ft_strchr("\'\"", heredocker.line_read[heredocker.i]))
		heredocker.i++;
	fd = forking_heredocs(final_str, heredocker, n_letters, local);
	heredoc_reader(new_heredocs, cur_heredocs, fd[0]);
	free(fd);
	return (heredocker.i);
}

static int	*forking_heredocs(char *final_str, t_heredocker heredocker, int n_letters, t_localenv *local)
{
	int		pid;
	int		*fd;
	
	fd = ft_calloc(2, sizeof(int));
	// j = 0;
	n_letters = 0;
	if (ft_strchr("\'\"", heredocker.line_read[heredocker.i]))
		heredocker.i++;
	while (!is_space(heredocker.line_read[heredocker.i + n_letters]) && !is_special_char(heredocker.line_read[heredocker.i+ n_letters])
		&& heredocker.line_read[heredocker.i + n_letters] != '\0' && !ft_strchr("\'\"", heredocker.line_read[heredocker.i + n_letters]))
		n_letters++;
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		switch_sig_default();
		write_to_fd(final_str, &(heredocker.line_read[heredocker.i]), fd, n_letters);
		free_split(local->content);
		free_split(local->sorted);
		free(local);
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
