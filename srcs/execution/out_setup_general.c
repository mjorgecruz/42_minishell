/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_setup_general.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:19:15 by masoares          #+#    #+#             */
/*   Updated: 2024/03/25 00:17:22 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	commands_sorter(t_token *cmd_list, t_info info, t_localenv *local)
{
	int			i;
	int			res;
	int			**fd;
	int			*pid;

	res = -1;
	i = 0;
	if (cmd_list->down != NULL)
		commands_sorter(cmd_list->down, info, local);
	if (cmd_list && cmd_list->cmds)
	{	
		fd = pipe_creator(*cmd_list, &pid);
		// pid[0] = fork();
		// if (pid[0] == 0)
		// {
			res = first_executioner(cmd_list, info, local, 0, fd);
		// 	exit(EXIT_SUCCESS);			
		// }
		while (cmd_list->cmds[i].cmds != NULL)
		{
			if (cmd_list->cmds[i].cmds != NULL && i > 0)
			{
				pid[i] = fork();
				if (pid[i] == 0)
				{
					res = inter_executioner(cmd_list, info, local, i, fd);
					exit(EXIT_SUCCESS);
				}	
			}
			i++;
		}
		// waitpid(pid[0], NULL, 0);
		// waitpid(pid[1], NULL, 0);

	}
	while (cmd_list->next != NULL && ((res == 0 && cmd_list->next_type == D_PIPE))) 
		cmd_list = cmd_list->next;
	if (cmd_list->next != NULL)	
		commands_sorter(cmd_list->next, info, local);
	return ;
}

int		inter_executioner(t_token *cmd_list, t_info info, t_localenv *local, int i, int **fd)
{
	char		**final_cmds;
	t_cmd_info	cmd_info;
	int		res;
	(void) local;

	printf("aqui");
	cmd_info.fd_in_out[0] = 0;
	cmd_info.fd_in_out[1] = 1;
	cmd_info.in_out[0] = UNDEF;
	cmd_info.in_out[1] = UNDEF;
	close_fd(&fd, i);
	dup2(fd[i - 1][0], STDIN_FILENO);
	if (cmd_list->cmds[i + 1].cmds != NULL)
		dup2(fd[i][1], STDOUT_FILENO);
	define_input(&(cmd_list->cmds[i]), &(cmd_info.fd_in_out[0]), &info.pos_heredoc, &(cmd_info.in_out[0]));
	if (cmd_info.fd_in_out[0] == -1 && cmd_info.in_out[0] != HEREDOC)
		return (0) ;
	define_output(&(cmd_list->cmds[i]), &(cmd_info.fd_in_out[1]), &(cmd_info.in_out[1]));
	final_cmds = clean_cmds(&(cmd_list->cmds[i]));
	set_id_flag_cmd(final_cmds, &(cmd_list->cmds[i].id));
	cmd_info.id = cmd_list->cmds[i].id;
	close(fd[i - 1][0]);
	close(fd[i][1]);
	res = solver(final_cmds, info, &cmd_info);
	return(res);
}

int		first_executioner(t_token *cmd_list, t_info info, t_localenv *local, int i, int **fd)
{
	char		**final_cmds;
	t_cmd_info	cmd_info;
	int		res;
	(void)		i;
	(void) local;

	cmd_info.fd_in_out[0] = 0;
	cmd_info.fd_in_out[1] = 1;
	cmd_info.in_out[0] = UNDEF;
	cmd_info.in_out[1] = UNDEF;
	if (cmd_list->cmds[1].cmds != NULL)
	{	
		close_fd(&fd, 0);
		dup2(fd[0][1], STDOUT_FILENO);
	}
	define_input(&(cmd_list->cmds[0]), &(cmd_info.fd_in_out[0]), &info.pos_heredoc, &(cmd_info.in_out[0]));
	if (cmd_info.fd_in_out[0] == -1 && cmd_info.in_out[0] != HEREDOC)
		return (0);
	define_output(&(cmd_list->cmds[0]), &(cmd_info.fd_in_out[1]), &(cmd_info.in_out[1]));
	final_cmds = clean_cmds(&(cmd_list->cmds[0]));
	set_id_flag_cmd(final_cmds, &(cmd_list->cmds[0].id));
	cmd_info.id = cmd_list->cmds[0].id;
	if (cmd_list->cmds[1].cmds != NULL)
	{	
		close(fd[0][1]);
	}
	res = solver(final_cmds, info, &cmd_info);
	return(res);
}

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

int	exec_correct_builtin(char **cmds, t_info info, t_builtin id, t_cmd_info cmd_info)
{
	t_localenv *local;
	
	local = (t_localenv *) malloc(sizeof(t_localenv));
	local->content = info.local;
	if (id == ECHOS)
		return (command_echo(cmds, local));
	else if (id == PWD)
		return (command_pwd());
	else if (id == EXPORT)
		return (command_export(cmds, local)) ;
	else if (id == ENV)
		return (command_env(local));
	else if (id == UNSET)
		return (command_unset(cmds, local));
	// // else if (id == EXIT)
	// // {
	// // 	command_exit(local_env, t_token *cmd_list, char ***heredocs);    como fazer?
	// // 	return ;
	// // }
	else if (id == CD)
		return (command_cd(cmds, local));
	else if (id == UNDEFINED)
		return(command_execve(cmds, local, info, cmd_info));
	free(local);
	return (1);
}
