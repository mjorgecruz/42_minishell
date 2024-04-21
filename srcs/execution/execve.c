/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:44:43 by masoares          #+#    #+#             */
/*   Updated: 2024/04/21 16:53:51 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

int	command_execve(char **cmds, t_localenv *local, t_info info,
	t_cmd_info cmd_info)
{
	char	**p_path;
	char	*paths;
	char	*origin_cmd;

	origin_cmd = NULL;
	paths = ft_getenv("PATH", local->content);
	if (paths == NULL)
		return (ex_code(execve_decider(cmds, local, info, cmd_info)), g_signal);
	p_path = ft_split(paths, ':');
	free(paths);
	if (ft_strchr(cmds[0], '/'))
		ex_code(execve_decider(cmds, local, info, cmd_info));
	else
	{
		origin_cmd = test_commands(cmds, p_path);
		if (!origin_cmd)
			ex_code(execve_decider(cmds, local, info, cmd_info));
		else
		{
			exec_not(origin_cmd);
			free(origin_cmd);
		}
	}
	free_split(p_path);
	return (g_signal);
}

char	*test_commands(char **cmds, char **p_path)
{
	char	*line;
	char	*cmd_0;
	int		i;

	cmd_0 = ft_strcpy(cmds[0]);
	line = cmds[0];
	cmds[0] = ft_strjoin("/usr/local/sbin/", cmd_0);
	free(line);
	i = 0;
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
	if (p_path[i])
		return (free(cmd_0), NULL);
	else
		return (cmd_0);
}

int	execve_decider(char **cmds, t_localenv *local, \
t_info info, t_cmd_info cmd_info)
{
	int	status;
	int	error;

	error = 0;
	status = 0;
	if (cmd_info.in_out[0] == HEREDOC)
		error = execve_heredoc(info, cmds, local);
	else if (cmd_info.in_out[0] == IN_DOC)
		error = execve_doc(cmd_info.fd_in_out[0], info, cmds, local);
	else
	{
		status = execve(cmds[0], cmds, local->content);
		exec_not(cmds[0]);
		error = errno;
	}
	if (status == -1)
		return (error);
	else
		return (0);
}

int	execve_heredoc(t_info info, char **cmds, t_localenv *local)
{
	int		fd[2];
	int		stdin;
	int		stdout;

	stdin = dup(STDIN_FILENO);
	stdout = dup(STDOUT_FILENO);
	pipe(fd);
	dup2(fd[1], STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(fd[0]);
	if ((*info.heredocs)[info.pos_heredoc])
	{
		ft_printf("%s", (*info.heredocs)[info.pos_heredoc]);
		free((*info.heredocs)[info.pos_heredoc]);
	}
	dup2(stdout, STDOUT_FILENO);
	close(stdout);
	execve(cmds[0], cmds, local->content);
	exec_not(cmds[0]);
	dup2(stdin, STDIN_FILENO);
	close(stdin);
	return (errno);
}

int	execve_doc(int fd_in, t_info info, char **cmds, t_localenv *local)
{
	(void) fd_in;
	(void) info;
	execve(cmds[0], cmds, local->content);
	exec_not(cmds[0]);
	return (errno);
}
