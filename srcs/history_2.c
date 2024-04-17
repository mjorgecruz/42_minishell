/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:31:08 by masoares          #+#    #+#             */
/*   Updated: 2024/04/17 01:55:47 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    first_fork(int fd0, int fd1, t_localenv *local_env, char *pwd)
{
    char    *line_read;
    int     res;

    res = 0;
    close(fd0);
	line_read = readline(pwd);
	free(pwd);
	free_split(local_env->content);
	free_split(local_env->sorted);
	free(local_env);
	if (!line_read)
	{
		res = 10;
		exit(res);
	}
	write(fd1, line_read, ft_strlen(line_read));
	exit(res);
}

void    line_reader(int fd0, int fd1, char **total_line)
{
    int     bread;
    char	buffer[21];
    
	close(fd1);
	bread = read(fd0, buffer, 20);
	buffer[bread] = 0;
	while (bread > 0)
	{
		*total_line = ft_strjoin_2(*total_line, buffer);
        bread = read(fd0, buffer, 20);
		buffer[bread] = 0;
	}
}

void    extra_fork(int fd0, int fd1, t_localenv *local, char * line_read)
{
    int     res;
    
    close(fd0);
	free_split(local->content);
	free_split(local->sorted);
	free(local);
    res = 0;
	g_signal = 0;
	line_read = readline("> ");
	if (!line_read)
	{
		res = 10;
    	exit(res);
	}
	if (is_only_spaces(line_read) == 0)
	{
		res = 20;
		free(line_read);
		exit(res);
	}
	write(fd1, line_read, ft_strlen(line_read));
	free(line_read);
	exit(res);
}
