/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:47:45 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/19 09:48:42 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*init_struct_cmd(void)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	new->content = NULL;
	new->next = NULL;
	new->down = NULL;
	return (new);
}

void	add_token(t_token **tokens, t_token *new)
{
	t_token	*trav;

	trav = NULL;
	if (*tokens == NULL)
		*tokens = new;
	else
	{
		trav = *tokens;
		while (trav->next != NULL)
			trav = trav->next;
		trav->next = new;
	}
}

bool	check_condition(int pos, char *str)
{
	if (str[pos] == '>' && str[pos + 1] && \
		is_special_char(str[pos + 1]))
		return (true);
	return (false);
}
