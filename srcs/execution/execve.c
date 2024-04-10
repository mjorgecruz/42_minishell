/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 09:49:36 by masoares          #+#    #+#             */
/*   Updated: 2024/04/10 14:33:57 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	command_execve(char **cmds, t_localenv *local, t_info info, t_cmd_info cmd_info)
{
	char	**p_path;

	p_path = ft_split(ft_getenv("PATH", local->content), ':');
	if (ft_strchr(cmds[0], '/'))
		ex_code(execve_decider(cmds, local, info, cmd_info));
	else
	{
		test_commands(cmds, p_path);
		ex_code(execve_decider(cmds, local, info, cmd_info));
	}
	return (free_split(p_path), g_signal);
}

void test_commands(char **cmds, char **p_path)
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
	free (cmd_0);
}

int		execve_decider(char **cmds, t_localenv *local, t_info info, t_cmd_info cmd_info)
{
	int		status;
	int		error;
	
	status = 0;
	if (cmd_info.in_out[0] == HEREDOC)
		status = execve_heredoc(info, cmds, local);
	else if (cmd_info.in_out[0] == IN_DOC)
	 	status = execve_doc(cmd_info.fd_in_out[0], info, cmds, local);
	else
	{
		status = execve(cmds[0], cmds, local->content);
		error = errno;
	}
	if (status == -1)
		return(error);
	else
		return (0);
}

int		execve_heredoc(t_info info, char **cmds, t_localenv *local)
{
	int		fd[2];
	int		stdin;
	int		stdout;
	int 	status;

	stdin = dup(STDIN_FILENO);
	stdout = dup(STDOUT_FILENO);
	pipe(fd);
	dup2(fd[1], STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(fd[0]);
	ft_printf("%s\n", (*info.heredocs)[info.pos_heredoc]);
	dup2(stdout, STDOUT_FILENO);
	close(stdout);
	status = execve(cmds[0], cmds, local->content);
	dup2(stdin, STDIN_FILENO);
	close(stdin);
	return (status);
}

int		execve_doc(int fd_in, t_info info, char **cmds, t_localenv *local)
{
	int		fd[2];
	char	buffer[21];
	int		bread;
	int		stdin;
	int		stdout;
	int 	status;

	(void) info;
	bread = 1; // also added this shit check it
	stdin = dup(STDIN_FILENO);
	stdout = dup(STDOUT_FILENO);
	pipe(fd);
	dup2(fd[1], STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	while (bread > 0)
	{
		bread = read(fd_in, buffer, 20);
		buffer[bread] = '\0';
		printf("%s", buffer);
	}
	dup2(stdout, STDOUT_FILENO);
	close(stdout);
	status = execve(cmds[0], cmds, local->content);
	dup2(stdin, STDIN_FILENO);
	close(stdin);
	return (status);
}
