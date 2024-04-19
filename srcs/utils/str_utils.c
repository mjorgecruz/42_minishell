/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/04/19 09:10:29 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ignore_in_quotes(char *str, int pos)
{
	if (str[pos] && str[pos] == D_QUOTE)
	{
		pos++;
		while (str[pos] && str[pos] != D_QUOTE)
			pos++;
	}
	else if (str[pos] && str[pos] == S_QUOTE)
	{
		pos++;
		while (str[pos] && str[pos] != S_QUOTE)
			pos++;
	}
	return (pos);
}

int	ignore_spaces(char *str, int pos)
{
	if (str)
	{
		while (str[pos] && is_space(str[pos]))
			pos++;
	}
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

	output = ft_calloc(ft_strlen(s) + 1, sizeof(char));
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
			return(true);
	return (false);
}