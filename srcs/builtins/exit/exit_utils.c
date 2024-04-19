/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:39:53 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/19 07:42:33 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	free_t_info(t_info info)
{
	int	i;

	i = 0;
	while (info.heredocs[i])
	{
		free(info.heredocs[i]);
		i++;
	}
	free(info.heredocs);
}

void	free_info_andenv(t_info info)
{
	int	i;

	i = 0;
	while (info.local->content[i])
	{
		free(info.local->content[i]);
		i++;
	}
	i = 0;
	while (info.local->sorted[i])
	{
		free(info.local->sorted[i]);
		i++;
	}
	free(info.local->content);
	free(info.local->sorted);
	free(info.local);
}

void	free_t_token(t_token *tok)
{
	int	i;

	i = 0;
	if (tok)
	{
		if (tok->content != NULL)
			free(tok->content);
		if (tok->cmds->cmds != NULL)
		{
			i = 0;
			while (tok->cmds[i].cmds)
			{
				free(tok->cmds[i].cmds);
				i++;
			}
			free(tok->cmds);
		}
		if (tok->down)
			free_t_token(tok->down);
		if (tok->next)
			free_t_token(tok->next);
	}
}

int	ex_code(int code)
{
	if (code == 298)
	{
		g_signal = 42;
		return (g_signal);
	}
	if (code == 5120 || code == 13)
	{
		g_signal = 126;
		return (g_signal);
	}
	if (code == 512)
	{
		g_signal = 127;
		return (g_signal);
	}
	if (code >= 256 || code <= -256)
	{
		g_signal = WEXITSTATUS(code);
		return (g_signal);
	}
	else
		g_signal = code;
	return (g_signal);
}
