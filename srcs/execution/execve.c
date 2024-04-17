/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 09:49:36 by masoares          #+#    #+#             */
/*   Updated: 2024/04/16 14:27:50 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
void set_mesage(char *cmd, int code, char *msg)
{
	(void ) cmd;
		//ft_putstr_fd(cmd, STDERR_FILENO);
		
		ft_putstr_fd( msg, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		ex_code(code);
}


void err_eacces_chooser(char *cmd)
{
	if (opendir(cmd) == NULL) 
		set_mesage(cmd, 127, ": Permission denied");
	else
		set_mesage(cmd, 127, ": Is a directory");
}

void err_enoent_chooser(char *cmd)
{
	if (ft_strchr(cmd, '/'))
		set_mesage(cmd, 127, " No such file or directory");
	else
		set_mesage(cmd, 127, ": command not found");
}

void exec_not(char *cmd)
{
	int i;
	int	count;

	count = 0;
	i = 0;
	while (cmd[i])
	{
		i = ignore_in_quotes(cmd, i);
		if (cmd[i] == '/')
			count++;
		if (cmd[i])
			i++;
	}
	if (errno == EACCES)
		err_eacces_chooser(cmd);
	else if (errno == ENOENT)
		err_enoent_chooser(cmd);

}

int	command_execve(char **cmds, t_localenv *local, t_info info, t_cmd_info cmd_info)
{
	char	**p_path;
	char	*paths;
	char *origin_cmd;
	
	origin_cmd = NULL;
	paths = ft_getenv("PATH", local->content);
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
		free_split(cmds);
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
		return(cmd_0);
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
		exec_not(cmds[0]);
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
	if ((*info.heredocs)[info.pos_heredoc])
	{
		ft_printf("%s", (*info.heredocs)[info.pos_heredoc]);
		free((*info.heredocs)[info.pos_heredoc]);
	}
	dup2(stdout, STDOUT_FILENO);
	close(stdout);
	status = execve(cmds[0], cmds, local->content);
	exec_not(cmds[0]);
	dup2(stdin, STDIN_FILENO);
	close(stdin);
	return (status);
}

int		execve_doc(int fd_in, t_info info, char **cmds, t_localenv *local)
{
	int		stdin;
	int		stdout;
	int 	status;

	(void) info;
	stdin = dup(STDIN_FILENO);
	stdout = dup(STDOUT_FILENO);
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	status = execve(cmds[0], cmds, local->content);
	exec_not(cmds[0]);
	dup2(stdin, STDIN_FILENO);
	close(stdin);
	return (status);
}
