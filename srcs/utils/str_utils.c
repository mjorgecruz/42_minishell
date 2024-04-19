/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 09:46:30 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/19 09:47:56 by luis-ffe         ###   ########.fr       */
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
	return (pos);
}

bool	is_space(char c)
{
	if ((c > 8 && c < 14) || c == ' ')
		return (true);
	return (false);
}

bool	is_special_char(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == '&')
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
