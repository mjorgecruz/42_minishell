/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_executor_5.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:16:41 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/19 15:24:39 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*token_creator(int i, int j, char *input, int type)
{
	t_token	*token;

	if (type == D_PIPE || type == D_AMP)
		token = create_node(j, i - 2, input, type);
	else
		token = create_node(j, i - 1, input, type);
	return (token);
}

bool	token_has_par(t_token *token)
{
	int	i;

	i = 0;
	while (token->content && token->content[i])
	{
		i = ignore_in_quotes(token->content, i);
		if (token->content[i] == '(')
			return (true);
		if (token->content[i])
			i++;
	}
	return (false);
}

int	ft_count_words(char *content, int pos)
{
	int		count;

	count = 0;
	pass_spaces(content, &pos);
	while (content[pos])
	{
		if (content[pos] == 34 || content[pos] == 39)
		{
			if (pos == 0 || content[pos - 1] != content[pos])
				count++;
			pass_quotes(content, &pos);
		}
		else if (ft_strchr("|", content[pos]) && \
			ft_strchr(">", content[pos - 1]))
			count++;
		pos++;
	}
	if (content[pos] && ft_strchr("|", content[pos + 1]) != NULL)
		pos += 2;
	return (count + 1);
}
