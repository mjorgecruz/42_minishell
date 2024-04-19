/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_executor_4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:15:35 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/19 15:17:36 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*trim_string(char *str)
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

t_type	type_definer(char *input, int *i)
{
	t_type	type;

	type = -1;
	if (input[*i] == '|')
	{
		if (input[(*i) + 1] == '|')
		{
			type = D_PIPE;
			(*i)++;
		}
	}
	else if (input[*i] == '&')
	{
		if (input[(*i) + 1] == '&')
			type = D_AMP;
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
	new_node->content[i] = 0;
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
