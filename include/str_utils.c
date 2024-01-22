/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 08:13:07 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/01/22 16:23:20 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
using in special parser at the moment
*/
#include "minishell.h"

bool	is_space(char c)
{
	if((c > 8 && c < 14) || c == ' ')
		return (true);
	return (false);
}

char *ft_strcpy(char *s)
{
	int i;
	char    *output;
    output = calloc(ft_strlen(s), sizeof(char));
	
	i = 0;
    while (s[i])
	{
        output[i] = s[i];
		i++;
	}
    return(output);
}

int	iterate_spaces(const char *str, int pos)
{
	while(is_space(str[pos]))
		pos++;
	return(pos);
}

t_token *init_struct_cmd(void)
{
	t_token *new;
	
	new = NULL;
	new->content = NULL;
	new->next = NULL;
	return (new);
}
void	add_token(t_token **tokens, t_token *new)
{
	t_token *trav;
	
	trav = NULL;
	if (*tokens == NULL)
		*tokens = new;
	else
	{
		trav = *tokens;
		while (trav->next != NULL)
		{
			trav = trav->next;
		}
		trav->next = new;
	}
}
