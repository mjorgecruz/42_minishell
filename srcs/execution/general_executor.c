/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:54:13 by masoares          #+#    #+#             */
/*   Updated: 2024/04/02 11:21:14 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

/* General execution file. Receives a valid full string and makes all organizes
all necessary operations This file contains the functions to divide the full
line read into segments separated by pipes*/

#include "../../includes/minishell.h"

void	general_executer(char *input, char ***heredocs, t_localenv *local)
{
	t_token	*cmd_list;
	t_info	info;
	
	cmd_list = NULL;
	info.heredocs = heredocs;
	info.pos_heredoc = -1;
	info.local = local;
	cmd_list = command_organizer(input);
	commands_separator(cmd_list);
	commands_sorter(cmd_list, info, local);
	//tester_function(&cmd_list);
	clean_cmd_list(cmd_list, heredocs);
}

t_token	*command_organizer(char *input)
{
	t_token	*list;
	t_type	type;
	t_token	*token;
	
	type = 0;
	token = NULL;
	list = NULL;
	command_divider(&list, input, type, token);
	return (list);
}

void	command_divider(t_token **list, char *input, t_type	type, t_token *token)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	type = 0;
	while (input[i])
	{
		if (input[i] == 34 || input[i] == 39)
			i = find_next(input, i);
		if (input[i] == '(')
			i = find_closed(input, i);
		if (!input[i])
			break;
		if ((input[i] == '|' && input[i + 1] == '|' ) || input[i] == '&')
		{
			type = type_definer(input, &i);
			token = token_creator(i, j, input, type);
			add_token(list, token);
			if (token_has_par(token))
				command_divider(&(token->down), trim_string(token->content), type, token);
			j = i + 1;
		}
		i++;
	}
	token = create_node(j, ft_strlen(input) - 1, input, NO_PIPE);
	add_token(list, token);
}

t_token *token_creator (int i, int j, char *input, int type)
{
	t_token *token;
	if (type == D_PIPE || type == D_AMP )
	{
		token = create_node(j, i - 2, input, type);
	}
	else
		token = create_node(j, i - 1, input, type);
	return (token);
}

bool token_has_par(t_token *token)
{
	int i;

	i = 0;
	while (token->content && token->content[i])
	{
		if (token->content[i] == '(')
			return (true);
		i++;
	}
	return (false);
}

char *trim_string(char *str)
{
	char	*trimmed;
	int		i;
	int		j;

	i = 0;
	j = 0;
	trimmed = ft_calloc(ft_strlen(str), sizeof(char));
	if (trimmed == NULL)
		return (NULL);
	while (str[i] != '(')
		i++;
	i++;
	while (str[i])
	{
		trimmed[j] = str[i];
		i++;
		j++;
	}
	while (trimmed[j] != ')')
	{
		trimmed[j] = '\0';
		j--; 
	}
	trimmed[j] = '\0';
	return (trimmed);
}

t_type type_definer(char *input, int *i)
{
	t_type	type;
	
	type = -1;
	if (input[*i] == '|')
		{
			if (input[(*i) + 1] == '|')
			{
				type  = D_PIPE;
				(*i)++;
			}
		}
	else if (input[*i] == '&')
	{
		if (input[(*i) + 1] == '&')
			type  = D_AMP;
		(*i)++;
	}
	else
		type = NO_PIPE;
	return (type);
}

int	find_next(char *input, int init_pos)
{
	int		i;

	i = init_pos + 1;
	while (input[i] && input[i] != input[init_pos])
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
	if (end < init)
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

int	find_closed(char *input, int i)
{
	int	par_count;

	par_count = 1;
	i++;
	while (par_count > 0)
	{
		if (input[i] == '(')
			par_count++;
		else if (input[i] == ')')
			par_count--;
		i++;
	}
	return (i);
}

int	tester_function(t_token **list)
{
	t_token	*trav;
	int		i;

	trav = *list;
	i = 0;
	while (trav)
	{
		i = 0;
		printf("content: %s ", trav->content);
		printf("pipe type: %d\n", trav->next_type);
		if (trav->down != NULL)
		{
			printf("down: %s , pipe type: %d, next: %s , pipe type: %d\n", trav->down->content, trav->down->next_type, trav->down->next->content, trav->down->next->next_type);
			tester_function(&trav->down);
		}
		if (trav->content == NULL)
		{
			printf("cmd( %d , %d ) -> ", 0, 0);
			printf("(null) \n");

		}
		else
		{
			while (i < pipe_counter(trav) + 1)
			{
				if (trav->cmds)
				{
					printf("id: %d\n", trav->cmds[i].id);
					printf("cmd(%d) -> ", i);
					printf("%s \n", trav->cmds[i].cmds);
					printf("cmd_redir: %d\n", trav->cmds[i].type);
				}
				i++;
			}
		}
		trav = trav->next;
	}
	return (1);
}
