/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 00:03:55 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/15 19:42:59 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../../includes/minishell.h"

static bool	is_arg_valid_numeric(const char *str)
{
	int i;
	
	i = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!ft_isdigit(str[i]))
		return (false);
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			i++;
		else
			return (false);
	}
	if (str[i] == '\0')
	{
		if (ft_strlen(str) > 10)
			return (false);
		return (true);
	}
	return (false);
}

static bool	exit_args_checker(char **cmds)
{
	if (!cmds[1])
		return (ex_code(0), true);
	if (cmds[2])
	{
		builtin_errors("exit: too many arguments", "\n", "");
		return (ex_code(1), false);
	}
	if (cmds[1] && !cmds[2])
	{
		if (is_arg_valid_numeric(cmds[1]))
			return (exit_code(ft_atoi(cmds[1])), true);
		else
		{
			builtin_errors("exit: ", 0, " numeric argument required\n");
			return (ex_code(2), false);   
		}
	}
	else
		return (ex_code(1), false);
}

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

void	command_exit(t_info info, char **cmds)
{
	(void) info;
	if (!exit_args_checker(cmds))
		return ;
	free_info_andenv(info);
	free_t_token(info.token);
	free(info.token);
	free_split(cmds);
	rl_clear_history();
	exit(ex_code(g_signal));
}
