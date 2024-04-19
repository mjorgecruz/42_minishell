/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:54:13 by masoares          #+#    #+#             */
/*   Updated: 2024/04/19 15:17:02 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* General execution file. Receives a valid full string and makes all organizes
all necessary operations This file contains the functions to divide the full
line read into segments separated by pipes*/

#include "../../includes/minishell.h"

void	general_executer(char *input, char ***heredocs, t_localenv *local)
{
	t_token	*cmd_list;
	t_info	info;
	int		i;

	i = 0;
	cmd_list = NULL;
	info.heredocs = heredocs;
	if ((*heredocs))
	{
		while ((*heredocs)[i] && (*heredocs)[i][0])
		{
			(*heredocs)[i] = expander_heredocs((*heredocs)[i], local);
			i++;
		}
	}
	info.pos_heredoc = -1;
	info.local = local;
	info.local = local;
	cmd_list = command_organizer(input);
	free(input);
	commands_separator(cmd_list);
	info.head = cmd_list;
	commands_sorter(cmd_list, info, local);
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

void	command_divider(t_token **list, char *in, \
t_type	type, t_token *token)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	type = 0;
	while (in[i])
	{
		if (!jumper_i(in, &i))
			break ;
		if (!in[i] || (in[i] == '|' && in[i + 1] == '|' ) || in[i] == '&')
		{
			type = type_definer(in, &i);
			token = token_creator(i, j, in, type);
			addings_tokens(list, token, type);
			j = i + 1;
		}
		if (in[i])
			i++;
	}
	if (j < ft_strlen(in))
	{
		token = create_node(j, ft_strlen(in) - 1, in, NO_PIPE);
		addings_tokens(list, token, type);
	}
}

int	jumper_i(char *input, int *i)
{
	if (input[*i] == 34 || input[*i] == 39)
		*i = find_next(input, *i);
	if (*i < ft_strlen(input) && input[*i] == '(')
		*i = find_closed(input, *i);
	if (*i >= ft_strlen(input) || !input[*i])
		return (0);
	return (1);
}

void	addings_tokens(t_token **list, t_token *token, t_type type)
{
	char	*trimmed;

	trimmed = NULL;
	add_token(list, token);
	if (token_has_par(token))
	{
		trimmed = trim_string(token->content);
		command_divider(&(token->down), trimmed, type, token);
		free(trimmed);
	}
}
