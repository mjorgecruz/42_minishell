/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_setup_general3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:49:22 by masoares          #+#    #+#             */
/*   Updated: 2024/04/18 15:50:17 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

void	set_id_flag_cmd(char **cmd, t_builtin *id)
{
	*id = get_builtin_id(cmd[0]);
	return ;
}

t_builtin	get_builtin_id(const char *str)
{
	if (!ft_strcmp(str, "cd") || !ft_strcmp(str, "\"cd\"") || !ft_strcmp(str, "\'cd\'"))
		return (CD);
	if (!ft_strcmp(str, "export") || !ft_strcmp(str, "\"export\"")
		|| !ft_strcmp(str, "\'export\'"))
		return (EXPORT);
	if (!ft_strcmp(str, "env") || !ft_strcmp(str, "\"env\"")
		|| !ft_strcmp(str, "\'env\'"))
		return (ENV);
	if (!ft_strcmp(str, "echo") || !ft_strcmp(str, "\"echo\"")
		|| !ft_strcmp(str, "\'echo\'"))
		return (ECHOS);
	if (!ft_strcmp(str, "unset") || !ft_strcmp(str, "\"unset\"")
		|| !ft_strcmp(str, "\'unset\'"))
		return (UNSET);
	if (!ft_strcmp(str, "exit") || !ft_strcmp(str, "\"exit\"")
		|| !ft_strcmp(str, "\'exit\'"))
		return (EXIT);
	if (!ft_strcmp(str, "pwd") || !ft_strcmp(str, "\"pwd\"")
		|| !ft_strcmp(str, "\'pwd\'"))
		return (PWD);
	if (!ft_strcmp(str, "printenv") || !ft_strcmp(str, "\"printenv\"")
		|| !ft_strcmp(str, "\'printenv\'"))
		return (PRINTENV);
	return (UNDEFINED);
}

int	exec_correct_builtin(char **cmds, t_info info, t_builtin id, t_cmd_info cmd_info)
{
	t_localenv *local;

	local = info.local;
	if (id == ECHOS)
		return (command_echo(cmds));
	else if (id == PWD)
		return (command_pwd(local));
	else if (id == EXPORT)
		return (command_export(cmds, local));
	else if (id == ENV)
		return (command_env(local));
	else if (id == UNSET)
		return (command_unset(cmds, local));
	else if (id == PRINTENV)
		return (command_printenv(cmds, local));
	else if (id == EXIT)
		command_exit(info, cmds);
	else if (id == CD)
		return (command_cd(cmds, local, 0));
	else if (id == UNDEFINED)
		return(command_execve(cmds, local, info, cmd_info));
	return (g_signal);
}
