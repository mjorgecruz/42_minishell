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

// void	commands_sorter(t_token **cmd_list)
// {
	
// }

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

// int	command_echo()
// {
// 	printf(...)
// }

// int	command_cd(char *line, char *paths)
// {
// }

// int	comand_pwd()
// {
	
// }
// int	command_export()
// {
	
// }
// int	command_unset()
// {
	
// }
// int	command_env()
// {
	
// }
// int	command_exit()
// {
	
// }
