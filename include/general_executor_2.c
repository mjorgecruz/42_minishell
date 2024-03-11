/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_executor_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:48:49 by masoares          #+#    #+#             */
/*   Updated: 2024/03/11 19:32:34 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*This file makes the segmentation of each part of the line read separated by 
pipes. The strings must be divided in parts in an array of structs*/

#include "minishell.h"

void	commands_separator(t_token *cmd_list)
{
	int		specials;
 
	while (cmd_list != NULL)
	{
		specials = 0;
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
				specials = specials_counter(cmd_list);
				cmd_list->cmds = (t_command *)malloc
				(sizeof(t_command) * (specials + 2));
			}
			fill_cmds(cmd_list, specials);	
		}
		else 
			commands_separator(cmd_list->down);
		cmd_list = cmd_list->next;
	}
}

void	fill_cmds(t_token *cmd_list, int specials)
{
	int	pos;
	int	i;

	pos = 0;
	i = 0;
	while (i < specials + 1)
	{
		cmd_list->cmds[i].cmds = mega_split(cmd_list->content, &pos);
		while (cmd_list->content[pos] == ' ')
			pos++;
		cmd_list->cmds[i].type = specials_selector(cmd_list, &pos);
		while (cmd_list && cmd_list->content && cmd_list->content[pos] 
			&& (cmd_list->content[pos] == ' '))
			//|| cmd_list->content[pos] == '|'))
			pos++;
		i++;
	}
	cmd_list->cmds[i].cmds = NULL;
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
		else if (ft_strchr("<>|", cmd_list->content[pos]))
		{
			while (ft_strchr("<>|", cmd_list->content[pos]))
				pos++;
			count++;
		}
		pos++;
	}
	return (count);
}

char	**mega_split(char *content, int *pos)
{
	char	**splitted;
	int		i;
	int		count;
	int		words;

	i = 0;
	count = 0;
	*pos = ignore_spaces(content, (*pos));
	words = ft_count_words(content, (*pos));
	if (words == 0)
		return (NULL);
	splitted = (char **)malloc(sizeof(char *) * (words + 1));
	if (splitted == NULL)
		return (NULL);
	while (i < words)
	{
		count = find_next_stop(content, *pos);
		splitted[i] = write_to_splitted(count, content, pos);
		while (content[*pos] == ' ' )
			(*pos)++;
		i++;
	}
	return (splitted[i] = NULL, splitted);
}

char	*write_to_splitted(int count, char *content, int *pos)
{
	int		j;
	char	*split_word;

	j = 0;
	split_word = ft_calloc(count + 1, sizeof(char));
	while (content[*pos] == ' ')
		(*pos)++;
	while (j < count)
	{
		split_word[j] = content[*pos];
		(*pos)++;
		j++;
	}
	return (split_word);
}

int	ft_count_words(char *content, int pos)
{
	int		count;

	count = 0;
	pass_spaces(content, &pos);
	while (content[pos])
	{
		if (content[pos] == 34 || content[pos] == 39)
		{
			if (pos == 0 || content[pos - 1] != content[pos])
				count++;
			pass_quotes(content, &pos);
		}
		else if (content[pos] == ' ' || ft_strchr("<>|", content[pos]))
		{
			pass_spaces(content, &pos);
			if (content[pos] && !ft_strchr("<>|", content[pos]) && content[pos] != 34 && content[pos] != 39)
				count++;
			else
			 	break ;	
		}
		pos++;
	}
	if (content[pos] && ft_strchr("<>|", content[pos + 1]) != NULL)
		pos += 2;
	return (count + 1);
}

t_special	specials_selector(t_token *cmd_list, int *pos)
{
	if (cmd_list->content[*pos] == '<')
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
	else if (cmd_list->content[*pos] == '|')
		return ((*pos)++, S_PIPE);
	else
		return ((*pos)++, NONE);
}

int	find_next_stop(char *content, int pos)
{
	int		asp_place;
	int		count;

	asp_place = 0;
	count = count_spaces(&pos, content);
	while (content[pos] && !ft_strchr("<>|", content[pos])
		&& content[pos] != ' ')
	{
		if (content[pos] == 34 || content[pos] == 39)
		{
			asp_place = pos++;
			count++;
			while (content[pos] != content[asp_place])
			{
				pos++;
				count++;
			}
		}
		count++;
		pos++;
	}
	if (!ft_strchr("<>|", content[pos]) || !content[pos])
		return (count);
	else
		return (count);
}

int	count_spaces(int *pos, char *content)
{
	int		count;

	count = 0;
	while (content[*pos] == ' ')
	{
		(*pos)++;
		count++;
	}
	return (count);
}

void	pass_spaces(char *content, int *pos)
{
	while (content[*pos] == ' ')
		(*pos)++;
}

void	pass_quotes(char *content, int *pos)
{
	int		asp_place;

	asp_place = *pos;
	if (content[*pos] == 34 || content[*pos] == 39)
		(*pos)++;
	while (content[*pos] != content[asp_place] && content[*pos] != '\0')
		(*pos)++;
}
