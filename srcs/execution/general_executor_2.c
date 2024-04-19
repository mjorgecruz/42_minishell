/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_executor_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:19:54 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/19 15:24:28 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*This file makes the segmentation of each part of the line read separated by 
pipes. The strings must be divided in parts in an array of structs*/

#include "../../includes/minishell.h"

void	commands_separator(t_token *cmd_list)
{
	int	pipes;

	while (cmd_list != NULL)
	{
		pipes = 0;
		if (cmd_list->down == NULL)
		{
			if (cmd_list->content == NULL)
			{
				cmd_list->cmds = (t_command *)malloc(sizeof(t_command));
				cmd_list->cmds->cmds = NULL;
				return ;
			}
			else
			{
				pipes = pipe_counter(cmd_list, 0);
				cmd_list->cmds = (t_command *)malloc(sizeof(t_command) * \
				(pipes + 2));
			}
			fill_cmds(cmd_list, pipes);
		}
		else
			commands_separator(cmd_list->down);
		cmd_list = cmd_list->next;
	}
}

void	fill_cmds(t_token *cmd_list, int pipes)
{
	int	pos;
	int	i;

	pos = 0;
	i = 0;
	while (i < pipes + 1)
	{
		cmd_list->cmds[i].cmds = mega_divider(cmd_list->content, &pos);
		while (cmd_list->content[pos] == ' ')
			pos++;
		cmd_list->cmds[i].type = pipe_selector(cmd_list, &pos);
		while (cmd_list && cmd_list->content && cmd_list->content[pos]
			&& (cmd_list->content[pos] == ' '))
			pos++;
		i++;
	}
	cmd_list->cmds[i].cmds = NULL;
}

int	pipe_counter(t_token *cmd_list, int pos)
{
	int		asp_place;
	int		count;

	count = 0;
	asp_place = 0;
	while (cmd_list->content[pos])
	{
		if (cmd_list->content[pos] == 34 || cmd_list->content[pos] == 39)
		{
			asp_place = pos;
			pos++;
			while (cmd_list->content[pos] != cmd_list->content[asp_place])
				pos++;
		}
		else if (ft_strchr("|", cmd_list->content[pos]) && \
			!ft_strchr(">", cmd_list->content[pos - 1]))
		{
			while (ft_strchr("|", cmd_list->content[pos]))
				pos++;
			count++;
		}
		pos++;
	}
	return (count);
}

char	*mega_divider(char *content, int *pos)
{
	char	*line;
	int		count;

	count = 0;
	*pos = ignore_spaces(content, (*pos));
	count = find_next_stop(content, *pos);
	line = write_to_line(count, content, pos);
	while (content[*pos] == ' ' )
		(*pos)++;
	return (line);
}

char	*write_to_line(int count, char *content, int *pos)
{
	int		j;
	char	*line;

	j = 0;
	line = ft_calloc(count + 2, sizeof(char));
	while (content[*pos] == ' ')
		(*pos)++;
	while (j < count)
	{
		line[j] = content[*pos];
		(*pos)++;
		j++;
	}
	line[j] = 0;
	return (line);
}
