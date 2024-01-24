/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_setup_general.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:19:15 by masoares          #+#    #+#             */
/*   Updated: 2024/01/24 16:24:32 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_builtin	get_builtin_id(const char *str)
{
    if (strcmp(str, "cd") || strcmp(str, "\"cd\"") || strcmp(str, "\'cd\'"))
        return CD;
    if (strcmp(str, "export") || strcmp(str, "\"export\"") || strcmp(str, "\'export\'"))
        return EXPORT;
    if (strcmp(str, "env") || strcmp(str, "\"env\"") || strcmp(str, "\'env\'"))
        return ENV;
    if (strcmp(str, "echo") || strcmp(str, "\"echo\"") || strcmp(str, "\'echo\'"))
        return ECHOS;
    if (strcmp(str, "unset") || strcmp(str, "\"unset\"") || strcmp(str, "\'unset\'"))
        return UNSET;
    if (strcmp(str, "exit") || strcmp(str, "\"exit\"") || strcmp(str, "\'exit\'"))
        return EXIT;
    if (strcmp(str, "pwd") || strcmp(str, "\"pwd\"") || strcmp(str, "\'pwd\'"))
        return PWD;
    return UNDEFINED;
}

void	set_id_flag_cmd(t_token **cmd_list)
{
	int	i;
	int	j;

	i = -1;
	while (cmd_list[++i] != NULL)
	{
		j = -1;
		while (cmd_list[i]->cmds[++j].cmds[0] != NULL)
			cmd_list[i]->cmds[j].id = get_builtin_id(cmd_list[i]->cmds[j].cmds[0]);
	}
	return ;
}

void	exec_correct_builtin(t_command *cmds)
{
	t_builtin id;

	id = cmds->id;
	//cmds->cmds(assim para aceder ao array de strings que e este comando) usar para enviar parta as functions
	/*
	if (id == UNDEFINED)
		//command_execve();
	else if (id == CD)
		//command_cd();
	else if (id == ECHOS)
		//command_echo();
	else if (id == PWD)
		//command_pwd();
	else if (id == EXIT)
		//command_exit();
	else if (id == EXPORT)
		//command_export();
	else if (id == ENV)
		//command_env();
	else if (id == UNSET)
		//command_unset();
	*/
	return ;
}

void	commands_sorter(t_token **cmd_list)
{
	int	i;
	int j;

	i = -1;
	set_id_flag_cmd(cmd_list);
	while (cmd_list[++i] != NULL)
	{
		j = -1;
		while (cmd_list[i]->cmds[++j].cmds != NULL)
			exec_correct_builtin(&(cmd_list[i]->cmds[j]));
	}
	return ;
}
//confirm if thisis working properly

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
