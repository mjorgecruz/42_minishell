/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_executor_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:25:13 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/19 15:25:43 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_special	pipe_selector(t_token *cmd_list, int *pos)
{
	if (cmd_list->content[*pos] == '|')
		return ((*pos)++, S_PIPE);
	else
		return ((*pos)++, NONE);
}

int	find_next_stop(char *content, int pos)
{
	int		asp_place;
	int		count;

	asp_place = 0;
	count = count_spaces(&pos, content);
	while (content[pos] && (!ft_strchr("|", content[pos]) || \
		(ft_strchr("|", content[pos]) && \
		ft_strchr(">", content[pos - 1]))))
	{
		if (content[pos] == 34 || content[pos] == 39)
		{
			asp_place = pos++;
			count++;
			while (content[pos] != content[asp_place])
			{
				pos++;
				count++;
			}
		}
		count++;
		pos++;
	}
	return (count);
}

int	count_spaces(int *pos, char *content)
{
	int		count;

	count = 0;
	while (content[*pos] == ' ')
	{
		(*pos)++;
		count++;
	}
	return (count);
}

void	pass_spaces(char *content, int *pos)
{
	while (content[*pos] == ' ')
		(*pos)++;
}

void	pass_quotes(char *content, int *pos)
{
	int		asp_place;

	asp_place = *pos;
	if (content[*pos] == 34 || content[*pos] == 39)
		(*pos)++;
	while (content[*pos] != content[asp_place] && content[*pos] != '\0')
		(*pos)++;
}
