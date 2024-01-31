/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:12:32 by masoares          #+#    #+#             */
/*   Updated: 2024/01/31 14:53:59 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*This file contains functions related to the history of the terminal*/

#include "minishell.h"

char	*get_line(char *total_line)
{
	char	*line_read;
	char	*vai_fora;
	char	*pwd;
	
	pwd = getcwd(NULL, 0);
	vai_fora = NULL;
	pwd = ft_strjoin("masoares&&luis-ffe@", pwd);
	line_read = readline(pwd);
	total_line = line_read;
	join_to_line(&total_line);
	if (total_line && *total_line)
		add_history(total_line);
	return (total_line);
}

void	join_to_line(char **total_line)
{
	char 	*line_read;
	char	*garbage;
	int		i;
	
	i = 0;
	garbage = NULL;
	line_read = "";
	if (open_parenthesis(*total_line)< 0)
		return(errors(1));
	if (end_pipe_and(*total_line) || open_parenthesis(*total_line) > 0)
	{
		ft_parser(*total_line);
		while (end_pipe_and(line_read) || is_only_spaces(line_read) >= 0 || open_parenthesis(*total_line) > 0)
		{
			line_read = readline("> ");
			if (is_only_spaces(line_read) == 0)
				continue ;
			add_space_line(total_line, line_read);
		}
	}
}

bool end_pipe_and(char *total_line)
{
	int		i;

	i = ft_strlen(total_line) - 1;
	while (total_line[i] == ' ' && i >= 0)
		i--;
	if (total_line[i] == '|' || total_line[i] == '&')
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
	ft_parser(*total_line);
}

int		open_parenthesis(char *total_line)
{
	int		i;
	int		count_open;

	i = 0;
	count_open = 0;
	while(total_line[i])
	{
		if (total_line[i] == '(')
			count_open++;
		if (total_line[i] == ')')
			count_open--;
		i++;
	}
	return (count_open);
}

char	*create_pc_name()
{
	char	*pwd;
	char	*name;
	char	*hostname;
	char	*vai_fora;
	
	pwd = get_end_path();
	
	hostname = getenv("HOSTNAME");
	
	name = ft_strjoin("masoares&&luis-ffe@", pwd);
}

char	*get_end_path(void)
{
	char	*garbage;
	char	*rest;
	int		i;
	int		count_bars;
	
	garbage = getcwd(NULL, 0);
	i = 0;
	count_bars = 0;
	
	
	free(garbage);
}

char	*get_hostname(void)
{
	char	*hostname;
	char	*garbage;
	int		i;
	
	garbage = getenv("HOSTNAME");
	while (hostname[i] != '.')
		i++;
	hostname = ft_calloc(i, sizeof(char));
	i = 0;
	while ()
}