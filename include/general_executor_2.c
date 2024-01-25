/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_executor_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:48:49 by masoares          #+#    #+#             */
/*   Updated: 2024/01/25 11:57:57 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*This file makes the segmentation of each part of the line read separated by 
pipes. The strings must be divided in parts in an array of structs*/

#include "minishell.h"

void	commands_separator(t_token *cmd_list)
{
	int		specials;
	int		i;
	int		pos;
	
	i = 0;
	pos = 0;
	while (cmd_list != NULL)
	{
		specials = specials_counter(cmd_list);
		cmd_list->cmds = (t_command *)malloc(sizeof(t_command) * (specials + 1));
		while (i < specials + 1)
		{
			cmd_list->cmds[i].cmds = mega_split(cmd_list->content, &pos);
			cmd_list->cmds[i].type = specials_selector(cmd_list);
			i++;
		}
		cmd_list = cmd_list->next;
	}
}

int	specials_counter(t_token *cmd_list)
{
	int		asp_place;
	int		count;
	int		pos;

	count = 0;
	asp_place = 0;
	pos = 0;
	while (cmd_list->content[pos])
	{
		if (cmd_list->content[pos] == 34 || cmd_list->content[pos] == 39)
		{
			asp_place = pos;
			pos++;
			while (cmd_list->content[pos] != cmd_list->content[asp_place])
				pos++;
		}
		else if (ft_strchr( "<>&", cmd_list->content[pos]))
		{
			while (ft_strchr("<>&", cmd_list->content[pos]))
				pos++;
			count++;
		}
		pos++;
	}
	return(0);
}

char	**mega_split(char *content, int *pos)
{
	char	**splitted;
	int		i;
	int		j;
	int 	count;
	
	i = 0;
	j = 0;
	count = 0;
	splitted = (char **)malloc(sizeof(char *) * (ft_count_words(content, (*pos)) + 1));
	if (splitted == NULL)
		return (NULL);
	while (content[*pos])
	{	
		count = find_next_stop(content, pos);
		splitted[i] = (char *)malloc(sizeof(char) * count + 1);
		if (splitted[i] == NULL)
			return (NULL);
		while(j < count)
		{
			splitted[i][j] = content[*pos];
			(*pos)++;
			j++;
		}
		i++;
	}
	splitted[i] = NULL;
	return (splitted);
}

int ft_count_words(char *content, int pos)
{
	int		asp_place;
	int		count;

	count = 0;
	asp_place = 0;
	while (content[pos] && ft_strchr( "<>&", content[pos]))
	{
		if (content[pos] == 34 || content[pos] == 39)
		{
			asp_place = pos;
			pos++;
			while (content[pos] != content[asp_place])
				pos++;
		}
		else if (ft_strchr(" ", content[pos]))
		{
			while (ft_strchr(" ", content[pos]))
				pos++;
			count++;
		}
	}
	if (ft_strchr( "<>&", content[pos + 1]))
		pos += 2;
	count = count + 1;
	return (count);
}

int	specials_selector(t_token *cmd_list)
{
	(void) cmd_list;
	return(0);
}

int find_next_stop(char *content, int *pos)
{
	int		asp_place;
	int		count;

	asp_place = 0;
	count = 0;
	while(content[*pos] && ft_strchr( "<>&", content[*pos]) && content[*pos] != ' ')
	{
		if (content[*pos] == 34 || content[*pos] == 39)
		{
			asp_place = *pos;
			(*pos)++;
			count++;
			while (content[*pos] != content[asp_place])
			{
				(*pos)++;
				count++;
			}
		}
		count++;
	}
	return (count);
}