/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:54:13 by masoares          #+#    #+#             */
/*   Updated: 2024/01/24 16:10:44 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* General execution file. Receives a valid full string and makes all organizes
all necessary operations This file contains the functions to divide the full
line read into segments separated by pipes*/

#include "minishell.h"

void	general_executer(char *input, char *paths)
{
	t_token	**cmd_list;

	cmd_list = command_organizer(input);
	//commands_separator(*cmd_list);
	//commands_sorter(cmd_list);
}

t_token	**command_organizer(char *input)
{
	t_token	**list;
	t_token	*token;
	int		j;

	j = 0;
	list = NULL;
	token = NULL;
	j = command_divider(list, token, input);
	if (ft_strlen(input) - 1 != j)
	{
		token = create_node(j, ft_strlen(input) - 1, input, NO_PIPE);
		add_to_list(list, token);
	}
	token = create_node(j, ft_strlen(input) - 1, input, NO_PIPE);
	add_to_list(list, token);
	return (list);
}

int	command_divider(t_token **list, t_token *token, char *input)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == 34 || input[39])
			i = find_next(input, i);
		if (input[i] == '|')
		{
			if (input[i + 1] == '|')
			{
				token = create_node(j, i - 1, input, D_PIPE);
				i++;
			}
			else
				token = create_node(j, i - 1, input, S_PIPE);
			add_to_list(list, token);
			j = i;
		}
		i++;
	}
	return (j);
}

int	find_next(char *input, int init_pos)
{
	int		i;

	i = init_pos + 1;
	while (input[i] != input[init_pos])
		i++;
	i++;
	return (i);
}

t_token	*create_node(int init, int end, char *input, t_type type)
{
	t_token	*new_node;
	int		i;
	int		j;

	i = 0;
	j = init;
	new_node = init_struct_cmd();
	new_node->next_type = NO_PIPE;
	new_node->content = ft_calloc(end + 1 - init, sizeof(char));
	new_node->cmds = NULL;
	while (j < end)
	{
		new_node->content[i] = input[j];
		i++;
		j++;
	}
	return (new_node);
}
