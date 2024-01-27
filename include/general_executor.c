/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:54:13 by masoares          #+#    #+#             */
/*   Updated: 2024/01/27 19:17:46 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* General execution file. Receives a valid full string and makes all organizes
all necessary operations This file contains the functions to divide the full
line read into segments separated by pipes*/

#include "minishell.h"

void	general_executer(char *input, char *paths)
{
	t_token	*cmd_list;
	(void) paths;

	cmd_list = command_organizer(input);
	commands_separator(cmd_list);
	tester_function(&cmd_list);
	//commands_sorter(cmd_list);
	clean_cmd_list(cmd_list, paths);
}

t_token	*command_organizer(char *input)
{
	t_token	*list;
	t_token	*token;
	int		j;

	j = 0;
	list = NULL;
	token = (t_token *) NULL;
	j = command_divider(&list, token, input);
	if ((int) ft_strlen(input) - 1 != j)
	{
		token = create_node(j, ft_strlen(input) - 1, input, NO_PIPE);
		add_token(&list, token);
	}
	else
	{
		token = create_node(0, 0, input, NO_PIPE);
		add_token(&list, token);
	}
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
		if (input[i] == 34 || input[i] == 39)
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
			i++;
			add_token(list, token);
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
	new_node->next_type = type;
	if (end <= init)
		new_node->content = (char *) NULL;
	else
	{
		new_node->content = ft_calloc(end + 3 - init, sizeof(char));
		while (j < end + 1)
		{
			new_node->content[i] = input[j];
			i++;
			j++;
		}
	}
	new_node->cmds = NULL;
	return (new_node);
}

int tester_function(t_token **list)
{
	t_token *trav;
	trav = *list;
	int		i;
	int		j;
	
	i = 0;
	j = 0;
	while (trav)
	{
		i = 0;
		printf("content: %s ", trav->content);
		printf("pipe type: %d\n", trav->next_type);
		while (i < specials_counter(*list) + 1)
		{
			j = 0;
			while (trav->cmds[i].cmds[j])
			{
				printf("cmd( %d , %d ) -> ", i, j);
				printf("%s \n", trav->cmds[i].cmds[j]);
				j++;
			}
			printf("cmd_redir: %d\n", trav->cmds[i].type);
			i++;
		}
		trav = trav->next;
	}
	return (1);
}