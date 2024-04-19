/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:12:32 by masoares          #+#    #+#             */
/*   Updated: 2024/04/19 15:39:42 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

/*This file contains functions related to the history of the terminal*/

#include "../includes/minishell.h"

char	*get_line(char *total_line, char ***heredocs, t_localenv *local_env)
{
	char	*pwd;
	int		res;

	res = 0;
	*heredocs = NULL;
	pwd = create_pc_name(local_env);
	switch_sig_function();
	total_line = readline(pwd);
	if (!total_line)
		all_initial_free(pwd, heredocs, local_env, res);
	free(pwd);
	if (!join_to_line(&total_line, heredocs, local_env))
	{
		if (total_line && *total_line)
		{
			add_history(total_line);
			free(total_line);
			total_line = NULL;
		}
	}
	else
		add_history(total_line);
	return (total_line);
}

void	all_initial_free(char *pwd, char ***heredocs, \
t_localenv *local_env, int res)
{
	free_split(*heredocs);
	free(pwd);
	free_split(local_env->content);
	free_split(local_env->sorted);
	free(local_env);
	printf("exit\n");
	exit(res);
}

int	writer_to_final(char **total_line, \
char **line_read, t_localenv *local)
{
	int		res;
	int		fd[2];
	int		pid;

	res = 0;
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		free(*total_line);
		extra_fork(fd[0], fd[1], local, *line_read);
	}
	handle_sigint_status();
	wait(&res);
	if (res == 2)
		return (printf("\n"), 0);
	read_to_line(total_line, line_read, fd);
	if (WEXITSTATUS(res) == 10)
		return (write(STDIN_FILENO, "\0", 1), 10);
	else if (WEXITSTATUS(res) == 20)
		return (20);
	return (res);
}

void	read_to_line(char **total_line, char **line_read, int *fd)
{
	int		bread;
	char	buffer[21];

	close(fd[1]);
	bread = read(fd[0], buffer, 20);
	buffer[bread] = 0;
	*line_read = *total_line;
	while (bread > 0)
	{
		*line_read = ft_strjoin_2(*line_read, buffer);
		bread = read(fd[0], buffer, 20);
		buffer[bread] = 0;
	}
	*total_line = *line_read;
}

bool	writer_from_input(char **total_line, char ***heredocs, \
t_localenv *local, int i)
{
	char	*line_read;
	int		res;

	if (end_pipe_and(*total_line) || open_parenthesis(*total_line) > 0)
	{
		if (!ft_parser(*total_line, &i))
			return (false);
		while (end_pipe_and(*total_line) || is_only_spaces(line_read) >= 0
			|| open_parenthesis(*total_line) > 0)
		{
			res = writer_to_final(total_line, &line_read, local);
			if (res == 0)
				break ;
			else if (res == 10)
				return (false);
			else if (res == 20)
				continue;
			if(!ft_parser(*total_line, &i))
				return (heredoc_writer(*total_line, heredocs, i, local),
					free_split(*heredocs), false);
			heredoc_writer(*total_line, heredocs, i, local);
		}
	}
	return (true);
}
