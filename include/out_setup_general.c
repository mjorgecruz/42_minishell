/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_setup_general.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:19:15 by masoares          #+#    #+#             */
/*   Updated: 2024/03/12 09:45:33 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	commands_sorter(t_token *cmd_list, t_info info, t_localenv *local)
{
	set_id_flag_cmd(cmd_list);
	solver(cmd_list, info, local);
	return ;
}

void	set_id_flag_cmd(t_token *cmd_list)
{
	int		j;

	if (cmd_list != NULL && cmd_list->down != NULL)
	{
		set_id_flag_cmd(cmd_list->down);
	}
	if (cmd_list != NULL && cmd_list->cmds != NULL)
	{
		j = 0;
		while (cmd_list->cmds && cmd_list->cmds->cmds != NULL 
			&& cmd_list->cmds[j].cmds != NULL && cmd_list->cmds[j].cmds[0] != NULL)
		{
			cmd_list->cmds[j].id 
				= get_builtin_id(cmd_list->cmds[j].cmds[0]);
			j++;
		}	
		set_id_flag_cmd(cmd_list->next);
	}
	if (cmd_list != NULL && cmd_list->cmds == NULL && cmd_list->next)
		set_id_flag_cmd(cmd_list->next);
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

int	exec_correct_builtin(t_command *cmds, int fd_in, int in, t_info info, t_localenv *local)
{
 	t_builtin id;
	
	(void) fd_in;
	(void) in;
	(void) info;
	id = cmds->id;
	if (id == ECHOS)
		return (command_echo(cmds->cmds, local));
	else if (id == PWD)
		return (command_pwd());
	else if (id == EXPORT)
		return (command_export(cmds->cmds, local)) ;
	else if (id == ENV)
		return (command_env(local));
	else if (id == UNSET)
		return (command_unset(cmds->cmds, local));
	// else if (id == EXIT)
	// {
	// 	command_exit(local_env, t_token *cmd_list, char ***heredocs);    como fazer?
	// 	return ;
	// }
	else if (id == CD)
		return (command_cd(cmds->cmds, local));
	else if (id == UNDEFINED)
		return(command_execve(cmds->cmds, local));
	return (1) ;
}

int	command_execve(char **cmds, t_localenv *local)
{
	int		pid;
	char	**p_path;
	int		i;
	char 	*line;
	char	*cmd_0;

	i = 0;
	cmd_0 = ft_strcpy(cmds[0]);
	p_path = ft_split(ft_getenv("PATH", local->content), ':');
	while (access(cmds[0], F_OK) != 0 && p_path[i] != NULL)
	{
		line = p_path[i];
		p_path[i] = ft_strjoin(p_path[i], "/");
		free(line);
		line = cmds[0];
		cmds[0] = ft_strjoin(p_path[i], cmd_0);
		free(line);
		i++;
	}
	pid = fork();
	if (pid == 0)
		execve(cmds[0], cmds, NULL);
	waitpid(pid, NULL, 0);
	return (free_split(p_path), 0);
}
