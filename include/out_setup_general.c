/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_setup_general.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:19:15 by masoares          #+#    #+#             */
/*   Updated: 2024/02/06 20:02:01 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	commands_sorter(t_token *cmd_list)
{
	set_id_flag_cmd(cmd_list);
	// verifitions of pipens olys lasts echos soulds bes echoeds
	while (cmd_list != NULL)
	{
		exec_correct_builtin(cmd_list->cmds);
		cmd_list = cmd_list->next;
	}
	return ;
}

void	set_id_flag_cmd(t_token *cmd_list)
{
	int		j;

	while (cmd_list != NULL)
	{
		j = 0;
		while (cmd_list->cmds && cmd_list->cmds->cmds != NULL && cmd_list->cmds[j].cmds != NULL && cmd_list->cmds[j].cmds[0] != NULL)
		{
			cmd_list->cmds[j].id 
				= get_builtin_id(cmd_list->cmds[j].cmds[0]);
			j++;
		}	
		cmd_list = cmd_list->next;
	}
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
	return (UNDEFINED);
}

void	exec_correct_builtin(t_command *cmds)
{
 	t_builtin id;

	id = cmds->id;
	if (id == ECHOS)
	{
		command_echo(cmds->cmds);
		return ;
	}
	else if (id == PWD)
	{
		command_pwd();
		return ;
	}
	// else if (id == UNDEFINED)
	// 	command_execve();
	// else if (id == CD)
	// 	command_cd();
	// else if (id == EXPORT)
	// 	//command_export();
	// else if (id == ENV)
	// 	//command_env();
	// else if (id == UNSET)
	// 	//command_unset();
	//else if (id == EXIT)
	// 	command_exit();
	return ;
}


int	command_execve(char *line, char *paths)
{
	char	**cmd;
	int		pid;
	char	**p_path;
	int		i;

	i = 0;
	p_path = ft_split(paths, ':');
	cmd = ft_split(line, ' ');
	ft_bzero(line, ft_strlen(line));
	line = ft_strjoin(line, cmd[0]);
	p_path[i] = ft_strjoin(p_path[i], "/");
	cmd[0] = ft_strjoin(p_path[i], cmd[0]);
	while (access(cmd[0], F_OK) != 0 && p_path[i] != NULL)
	{
		p_path[i] = ft_strjoin(p_path[i], "/");
		cmd[0] = ft_strjoin(p_path[i], line);
		i++;
	}
	pid = fork();
	if (pid == 0)
		execve(cmd[0], cmd, NULL);
	waitpid(pid, NULL, 0);
	return (free(line), free_split(p_path), free_split(cmd), 1);
}
