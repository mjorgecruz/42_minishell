/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 08:13:07 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/01/31 10:16:00 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*always returns the position
on finding quotes ignores them and any spaces or other chars until it finds special chars outside the quotes
returning their position
*/

int	ignore_in_quotes(const char *str, int pos)               // ok!!!!!
{
	while (str[pos] && !is_special_char(str[pos]))
	{
		if (str[pos] == D_QUOTE)
		{
			pos++;
			while (str[pos] && str[pos] != D_QUOTE)
				pos++;
		}
		else if (str[pos] == S_QUOTE)
		{
			pos++;
			while (str[pos] && str[pos] != S_QUOTE)
				pos++;
		}
		pos++;
	}
	return (pos);
}

//needs to receive the position of a space to start counting the spaces and returns pos of first non space
int	ignore_spaces(const char *str, int pos)
{
	while(is_space(str[pos]))
		pos++;
	return(pos);
}

bool	is_space(char c)
{
	if ((c > 8 && c < 14) || c == ' ')
		return (true);
	return (false);
}

bool	is_special_char(char c)
{
	if (c == '|' || c == '>' || c == '<' ||  c == '&')
		return (true);
	return (false);
}

char	*ft_strcpy(char *s)
{
	int		i;
	char	*output;

	output = ft_calloc(ft_strlen(s), sizeof(char));
	i = 0;
	while (s[i])
	{
		output[i] = s[i];
		i++;
	}
	return (output);
}

t_token	*init_struct_cmd(void)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	new->content = NULL;
	new->next = NULL;
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
