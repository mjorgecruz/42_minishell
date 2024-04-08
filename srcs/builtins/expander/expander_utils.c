/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 00:04:37 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/04 15:35:36 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool	is_str_empty(char *str)
{
	if (!str)
		return (true);
	if (*str == '\0' || *str == '\n' || *str == '\t')
		return (true);
	return (false);
}

int	quotes_counter(char *cmd)
{
	int		i;
	char	quote;

	i = 0;
	quote = cmd[i];
	while (cmd[i] && cmd[i] == quote)
		i++;
	return (i);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	len;

	len = ft_strlen(s);
	if (len < n)
		n = len;
	dup = (char *)malloc(sizeof(char) * (n + 1));
	if (!dup)
		return (NULL);
	ft_memcpy(dup, s, n);
	dup[n] = '\0';
	return (dup);
}

int	quotation_size(char *cmd, int start)
{
	char	quote;
	int		i;

	i = start + 1;
	quote = cmd[start];
	while (cmd[i] != '\0' && cmd[i] != quote)
		i++;
	return (i - start + 1);
}

void	print_list(t_lstexpand *head)
{
	while (head != NULL)
	{
		ft_printf("Status: %d, Content: %s\n", head->status, head->content);
		head = head->next;
	}
}