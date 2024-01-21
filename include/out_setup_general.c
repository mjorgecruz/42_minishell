/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_setup_general.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:19:15 by masoares          #+#    #+#             */
/*   Updated: 2024/01/20 23:58:26 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int command_executer(char *line, char *paths)
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
	while(access(cmd[0], F_OK) != 0 && p_path[i] != NULL)
	{
		p_path[i] = ft_strjoin(p_path[i], "/");
		cmd[0] = ft_strjoin(p_path[i], line);
		i++;
	}
	pid = fork();
	if (pid == 0)
		execve(cmd[0], cmd, NULL);
	waitpid(pid, NULL, 0);
	free_split(cmd);
	free_split(p_path);
	free(line);
	return (1);
}
