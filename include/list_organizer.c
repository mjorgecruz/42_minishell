/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_organizer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:40:38 by masoares          #+#    #+#             */
/*   Updated: 2024/02/26 15:26:43 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int list_organizer(t_token **list, char *input)
{
	int	i;
	int par_count;
	int	j;
	int	beg;
	
	beg = 0;
	par_count = 0;
	i = 0;
	j = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '(')
		{
			if (par_count == 0)
			{
				create_list_node(list, input, i - 1, beg);
				j = i;
			}
			par_count++;
		}
		if (input[i]  == ')')
		{
			par_count--;
			i++;
		}
		if (j!=0 && par_count == 0)
		{
			while (input[i] != '\0' && (input[i] == ' ' || input[i] == '&' || input[i] == '|'))
				i++;
			beg = i;
			create_list_node(list, input, i - 1, j);
			j = 0;
		}
		i++;
	}
	if (beg != i)
		create_list_node(list, input, i - 1, beg);
	return (0);
}

int create_list_node(t_token **list, char *input, int  i, int beg)
{
	t_token	*new;
	t_token *trav;
	
	trav = *list;
	new = create_list_new_node(input, i, beg);
	if (*list == NULL)
		*list = new;
	else
	{
		while (trav->next != NULL)
		{
			trav = trav->next;
		}
		trav->next = new;
	}
	return (0);
}

t_token *create_list_new_node(char *input, int i, int beg)
{
	t_token	*node;
	int			j;

	j = 1;
	node = (t_token *)malloc(sizeof(t_token));
	node->down = NULL;
	node->next = NULL;
	node->cmds = NULL;
	node->content = (char *)ft_calloc(sizeof(char), (i - beg + 1));
	if (node->content == NULL)
		return (NULL);
	while (j <= i - beg)
	{
		node->content[j] = input [j + beg];
		j++;
	}
	node->content[j] = '\0';
	return (node);
}