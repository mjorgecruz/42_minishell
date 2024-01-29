/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_executor_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:48:49 by masoares          #+#    #+#             */
/*   Updated: 2024/01/27 19:05:42 by masoares         ###   ########.fr       */
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
		cmd_list->cmds = (t_command *)malloc(sizeof(t_command) * (specials + 2));
		pos = 0;
		i = 0;
		while (i < specials + 1)
		{
			cmd_list->cmds[i].cmds = mega_split(cmd_list->content, &pos);
			while(cmd_list->content[pos] == ' ')
				pos++;
			cmd_list->cmds[i].type = specials_selector(cmd_list, &pos);
			while(cmd_list->content[pos] && (cmd_list->content[pos] == ' ' || cmd_list->content[pos] == '|'))
				pos++;
			i++;
		}
		cmd_list->cmds[i].cmds = NULL;
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
	return(count);
}

char	**mega_split(char *content, int *pos)
{
	char	**splitted;
	int		i;
	int		j;
	int 	count;
	int		words;
	
	i = 0;
	j = 0;
	count = 0;
	words = ft_count_words(content, (*pos));
	splitted = (char **)malloc(sizeof(char *) * (words + 1));
	if (splitted == NULL)
		return (NULL);
	while (i < words)
	{	
		count = find_next_stop(content, *pos);
		splitted[i] = ft_calloc(count + 1, sizeof(char));
		j = 0;
		while (content[*pos] == ' ')
			(*pos)++;
		while(j < count)
		{
			splitted[i][j] = content[*pos];
			(*pos)++;
			j++;
		}
		while (content[*pos] == ' ')
			(*pos)++;
		i++;
	}
	return (splitted[i] = NULL, splitted);
}

int ft_count_words(char *content, int pos)
{
	int		asp_place;
	int		count;

	count = 0;
	asp_place = 0;
	while (content[pos] == ' ')
		pos++;
	while (content[pos] && !ft_strchr( "<>&", content[pos]))
	{
		if (content[pos] == 34 || content[pos] == 39)
		{
			asp_place = pos;
			pos++;
			while (content[pos] != content[asp_place])
				pos++;
		}
		else if (content[pos] == ' ')
		{
			while (content[pos] == ' ')
				pos++;
			if ( content[pos] && !ft_strchr( "<>&", content[pos]))
				count++;
			else
				break;
		}
		pos++;
	}
	if (content[pos] && ft_strchr( "<>&", content[pos + 1]) != NULL)
		pos += 2;
	count = count + 1;
	return (count);
}

t_special	specials_selector(t_token *cmd_list, int *pos)
{
	if(cmd_list->content[*pos] == '<')
	{
		if (cmd_list->content[(*pos) + 1] == '<')
			return ((*pos) += 2, D_REDIR_IN);
		else
			return ((*pos)++, S_REDIR_IN);
	}
	else if (cmd_list->content[*pos] == '>')
	{
		if (cmd_list->content[(*pos) + 1] == '>')
			return ((*pos) += 2, D_REDIR_OUT);
		else
			return ((*pos)++, S_REDIR_OUT);
	}
	else if (cmd_list->content[*pos] == '&')
	{
		if (cmd_list->content[(*pos) + 1] == '&')
			return ((*pos) += 2, D_AMPER);
		else
			return ((*pos)++, S_AMPER);
	}
	else
		return ((*pos)++, NONE);
}

int find_next_stop(char *content, int pos)
{
	int		asp_place;
	int		count;

	asp_place = 0;
	count = 0;
	while (content[pos] == ' ')
	{
		pos++;
		count++;
	}
	while(content[pos] && !ft_strchr( "<>&", content[pos]) && content[pos] != ' ')
	{
		if (content[pos] == 34 || content[pos] == 39)
		{
			asp_place = pos;
			(pos)++;
			count++;
			while (content[pos] != content[asp_place])
			{
				(pos)++;
				count++;
			}
		}
		count++;
		(pos)++;
	}
	return (count);
}
