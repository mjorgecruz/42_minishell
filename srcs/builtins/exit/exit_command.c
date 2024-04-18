/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 00:03:55 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/18 15:04:21 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../../includes/minishell.h"

static bool	is_arg_valid_numeric(const char *str)
{
	int	i;

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
		bi_err("exit: too many arguments", "\n", "");
		return (ex_code(1), false);
	}
	if (cmds[1] && !cmds[2])
	{
		if (is_arg_valid_numeric(cmds[1]))
			return (ex_code(ft_atoi(cmds[1])), true);
		else
		{
			bi_err("exit: ", 0, "numeric argument required\n");
			return (ex_code(2), false);
		}
	}
	else
		return (ex_code(1), false);
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
