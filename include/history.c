/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:12:32 by masoares          #+#    #+#             */
/*   Updated: 2024/02/11 18:08:03 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*This file contains functions related to the history of the terminal*/

#include "minishell.h"

char	*get_line(char *total_line)
{
	char	*line_read;
	char	*pwd;
	
	pwd = create_pc_name();
	line_read = readline(pwd);
	if (!line_read)
	{
		printf("exit\n");
		free(pwd);
		exit(EXIT_SUCCESS);
	}
	total_line = line_read;
	if (!join_to_line(&total_line))
	{
		if (total_line && *total_line)
			add_history(total_line);
		free(total_line);
	}
	if (total_line && *total_line)
		add_history(total_line);
	free(pwd);
	return (total_line);
}

bool	join_to_line(char **total_line)
{
	char 	*line_read;
	int		heredocs;

	heredocs = 0;
	line_read = "";
	if (open_parenthesis(*total_line) < 0)
		return(errors(SYNTAX_CLOSE_P, NULL), false);
	if (end_pipe_and(*total_line) || open_parenthesis(*total_line) > 0)
	{
		if(!ft_parser(*total_line))
			return (false);
		heredocs = heredoc_count(*total_line);
		if (heredocs > 0)
			heredoc_writer(*total_line, heredocs);
		while (end_pipe_and(line_read) || is_only_spaces(line_read) >= 0 || open_parenthesis(*total_line) > 0)
		{
			line_read = readline("> ");
			if (!line_read)
				return (false);
			if (is_only_spaces(line_read) == 0)
				continue ;
			add_space_line(total_line, line_read);
		}
	}
	return (true);
}

bool end_pipe_and(char *total_line)
{
	int		i;

	i = ft_strlen(total_line) - 1;
	while (total_line[i] == ' ' && i >= 0)
		i--;
	if (total_line[i] && (total_line[i] == '|' || total_line[i] == '&'))
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
		if (total_line[i] == '\'' || total_line[i] == '"')
			pass_quotes(total_line, &i);
		if (total_line[i] == '(')
			count_open++;
		if (total_line[i] == ')')
			count_open--;
		i++;
	}
	return (count_open);
}

char	*create_pc_name(void)
{
	char	*pwd;
	char	*name;
	char	*vai_fora;
	
	pwd = get_end_path();
	name = ft_strjoin("masoares&&luis-ffe@", "minishell:");
	vai_fora = name;
	name = ft_strjoin(name, pwd);
	free(vai_fora);
	free(pwd);
	return (name);
}

char	*get_end_path(void)
{
	char	*garbage;
	char	*rest;
	int		i;
	int		j;
	int		count_bars;
	
	garbage = getcwd(NULL, 0);
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
