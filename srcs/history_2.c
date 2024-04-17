/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:31:08 by masoares          #+#    #+#             */
/*   Updated: 2024/04/17 12:15:12 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"

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
	switch_sig_new();
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