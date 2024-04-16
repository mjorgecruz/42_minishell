/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:12:32 by masoares          #+#    #+#             */
/*   Updated: 2024/04/17 00:50:57 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*This file contains functions related to the history of the terminal*/

#include "../includes/minishell.h"

char	*get_line(char *total_line, char ***heredocs, t_localenv *local_env)
{
	char	*pwd;
	int		pid;
	int		fd[2];
	int		res;
	
	res = 0;
	*heredocs = NULL;
	pwd = create_pc_name(local_env);
	switch_sig_function();
	total_line = ft_strdup("");
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		free(total_line);
	 	first_fork(fd[0], fd[1], local_env, pwd);
	}
	waitpid(0, &res, 0);
	line_reader(fd[0], fd[1], &total_line);
	free(pwd);
	if (WEXITSTATUS(res) == 10)
	{
		printf("exit\n");
		free_split(local_env->content);
		free_split(local_env->sorted);
		free(local_env);
		free(total_line);
		exit(10);
	}
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



bool	join_to_line(char **total_line, char ***heredocs, t_localenv *local)
{
	char 	*line_read;
	int		i;
	int		pid;
	int		fd[2];
	int		res;
	int		bread;
	char	buffer[21];

	i = 0;
	if(!ft_parser(*total_line, &i))
	{
		heredoc_writer(*total_line, heredocs, i, local);
		return (false);
	}
	heredoc_writer(*total_line, heredocs, i, local);
	if (end_pipe_and(*total_line) || open_parenthesis(*total_line) > 0)
	{
		i = 0;
		if(!ft_parser(*total_line, &i))
			return (false);
		while (end_pipe_and(*total_line) || is_only_spaces(line_read) >= 0
			|| open_parenthesis(*total_line) > 0)
		{
			res = 0;
			pipe(fd);
			pid = fork();
			if (pid == 0)
			{
				free(*total_line);
				extra_fork(fd[0], fd[1], local, line_read);
			}
			wait(&res);
			close(fd[1]);
			bread = read(fd[0], buffer, 20);
			buffer[bread] = 0;
			line_read = *total_line;
			while (bread > 0)
			{
				line_read = ft_strjoin_2(line_read, buffer);
				bread = read(fd[0], buffer, 20);
				buffer[bread] = 0;
			}
			*total_line = line_read;
			if (WEXITSTATUS(res) == 10)
			{
				write(STDIN_FILENO, "\0", 1);
				return (false);
			}
			else if (WEXITSTATUS(res) == 20)
				continue;
			if(!ft_parser(*total_line, &i))
			{
				heredoc_writer(*total_line, heredocs, i, local);
				return (false);
			}
			heredoc_writer(*total_line, heredocs, i, local);
			i = 0;
		}
	}
	if(!ft_parser(*total_line, &i))
		return (free(total_line), false);
	return (true);
}

bool end_pipe_and(char *total_line)
{
	int		i;

	i = ft_strlen(total_line) - 1;
	while (i >= 0 && total_line[i] == ' ')
		i--;
	if (i >= 0 && (total_line[i] == '|' || total_line[i] == '&'))
		return (true);
	else
		return (false);
}

int is_only_spaces(char *total_line)
{
	int		i;
	int		count;

	count = 0;
	i = ft_strlen(total_line) - 1;
	while (total_line[i] == ' ' && i >= 0)
	{
		i--;
		count++;
	}
	if (total_line[0] == ' ' || total_line[0] == '\0')
		return (count);
	else
		return (-1);
}

void	add_space_line(char **total_line, char *line_read)
{
	char *garbage;
	
	garbage = *total_line;
	*total_line = ft_strjoin(*total_line, " ");
	free(garbage);
	garbage = *total_line;
	*total_line = ft_strjoin(*total_line, line_read);
	free(garbage);
}


int		open_parenthesis(char *total_line)
{
	int		i;
	int		count_open;

	i = 0;
	count_open = 0;
	while(total_line[i])
	{
		if (total_line[i] == '\'' || total_line[i] == '"')
			pass_quotes(total_line, &i);
		if (total_line[i] == '(')
			count_open++;
		if (total_line[i] == ')')
			count_open--;
		if (count_open < 0)
			return (-1);
		i++;
	}
	return (count_open);
}

char	*create_pc_name(t_localenv *local_env)
{
	char	*pwd;
	char	*name;
	char	*vai_fora;
	
	pwd = get_end_path(local_env);
	name = ft_strjoin("masoares&&luis-ffe@", "minishell:");
	vai_fora = name;
	name = ft_strjoin(name, pwd);
	free(vai_fora);
	free(pwd);
	return (name);
}

char	*get_end_path(t_localenv *local_env)
{
	char	*garbage;
	char	*rest;
	int		i;
	int		j;
	int		count_bars;
	
	garbage = getcwd(NULL, 0);
	if (garbage == NULL)
		garbage = ft_getenv("PWD", local_env->content);
	i = 0;
	j = 2;
	count_bars = 0;
	while (garbage[i] != '\0' && count_bars < 4)
	{
		if (garbage[i] == '/')
			count_bars++;
		i++;
	}
	rest = ft_calloc(ft_strlen(garbage) - i + 1 + 4, sizeof(char));
	rest[0] = '~';
	rest[1] = '/';
	while (garbage[i] != '\0')
		rest[j++] = garbage[i++];
	return (rest[j] = '$', rest[j + 1] = ' ', rest[j + 2] = '\0', free(garbage), rest);
}
