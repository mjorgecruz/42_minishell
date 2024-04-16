/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:29:43 by masoares          #+#    #+#             */
/*   Updated: 2024/04/17 00:11:23 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	heredoc_reader(char ***new_heredocs, int *cur_heredocs, int fd);
static int	forking_heredocs(char *final_str, t_heredocker heredocker, t_localenv *local, char ***new_heredocs);
static void	heredoc_word(char *str, char *word);
static int	write_to_fd(char *final_str, int *fd, char *str);

int heredoc_creator(char ***new_heredocs, int *cur_heredocs, t_heredocker heredocker, t_localenv *local)
{
	char	*final_str;
	int		fd;
	(void)	local;

	final_str = NULL;
	heredocker.i = ignore_spaces(heredocker.line_read, heredocker.i + 1);
	(*new_heredocs)[*cur_heredocs] = NULL;
	fd = forking_heredocs(final_str, heredocker, local, new_heredocs);
	heredoc_reader(new_heredocs, cur_heredocs, fd);
	return (heredocker.i);
}

static int	forking_heredocs(char *final_str, t_heredocker heredocker, t_localenv *local, char ***new_heredocs)
{
	int		pid;
	int		fd[2];
	char	word[4096];

	heredoc_word(&(heredocker.line_read[heredocker.i]), word);
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		free_split(local->content);
		free_split(local->sorted);
		free(local);
		free_split(*new_heredocs);
		write_to_fd(final_str, fd, word);
		free(heredocker.line_read);
		exit(EXIT_SUCCESS);
	}
	switch_sig_function();
	waitpid(0, NULL, 0);
	close(fd[1]);
	return (fd[0]);
}

static void	heredoc_word(char *str, char *word)
{
	int		i;
	int		j;
	char	asps;
	
	i = -1;
	j = 0;
	while (++i < 4096)
		word[i] = 0;
	i = 0;
	while (str[i] && is_space(str[i]))
		i++;
	while (str[i] != '\0' && !is_special_char(str[i]) && !is_space(str[i]))
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			asps = str[i];
			i++;
			while (str[i] != asps)
			{
				word[j] = str[i];
				i++;
				j++;
			}
			i++;
		}
		if (str[i])
		{
			word[j] = str[i];
			i++;
			j++;
		}
	}
}

static int write_to_fd(char *final_str, int *fd, char *str)
{
	close(fd[0]);
	switch_sig_default();
	add_partials(&(final_str), str);
	write(fd[1], final_str, ft_strlen(final_str));
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
