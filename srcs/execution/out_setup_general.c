/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_setup_general.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:19:15 by masoares          #+#    #+#             */
/*   Updated: 2024/04/09 11:36:19 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

void	commands_sorter(t_token *cmd_list, t_info info, t_localenv *local)
{
	int			i;
	int			res;

	res = -1;
	i = 0;
	if (cmd_list->down != NULL)
		commands_sorter(cmd_list->down, info, local);
	if (cmd_list && cmd_list->cmds)
	{
		if (cmd_list->cmds[i + 1].cmds == NULL && cmd_list->cmds[i].cmds[0] != 0)
			res = inter_executioner(cmd_list, info, local, i);
		else
			res = mult_cmd_executer(cmd_list, info, local, i);
		ft_printf("%d\n", res);
	}
	while (cmd_list->next != NULL && ((res == 0 && cmd_list->next_type == D_PIPE))) 
		cmd_list = cmd_list->next;
	if (cmd_list->next != NULL)	
		commands_sorter(cmd_list->next, info, local);
	return ;
}

int		mult_cmd_executer(t_token *cmd_list, t_info info, t_localenv *local, int i)
{
	int			pid;
	int			stdin;
	int			fd[2];
	int			res;
	
	stdin = dup(STDIN_FILENO);
	res = -1;
	while (cmd_list->cmds[i].cmds)
	{
		if (cmd_list->cmds[i].cmds[0] != 0)
		{
			pipe(fd);
			pid = fork();
			if (pid == 0)
			{
				pied_piper(cmd_list, fd, i, &stdin);
				res = inter_executioner(cmd_list, info, local, i);
				exit(res);
			}
			dup2(fd[0], stdin);
			close(fd[0]);
			close(fd[1]);
		}
		i++;
	}
	close(stdin);
	return(waiter_function(cmd_list));
}

int		pied_piper(t_token *cmd_list, int *fd, int i, int *stdin)
{
	if (cmd_list->cmds[i + 1].cmds)
		dup2((fd)[1], STDOUT_FILENO);
	if(i > 0)
		dup2(*stdin, STDIN_FILENO);
	close((fd)[0]);
	close((fd)[1]);
	close(*stdin);
	return (1);
}

int		waiter_function(t_token *cmd_list)
{
	int		i;
	int		res;
	
	res = 0;
	i = 0;
	while (cmd_list->cmds[i].cmds)
	{
		wait(&res);
		i++;
	}
	return(res);
}

int		inter_executioner(t_token *cmd_list, t_info info, t_localenv *local, int i)
{
	char		**final_cmds;
	t_cmd_info	cmd_info;
	int			res;
	int			pid;
	int			j;
	
	(void) local;
	pid = 0;
	j = 0;
	cmd_info.fd_in_out[0] = 0;
	cmd_info.fd_in_out[1] = 1;
	cmd_info.in_out[0] = UNDEF;
	cmd_info.in_out[1] = UNDEF;
	while (j < i)
	{
		define_input(&(cmd_list->cmds[j]), &(cmd_info.fd_in_out[0]),
			&info.pos_heredoc, &(cmd_info.in_out[0]));
		j++;
	}
	if (wildcard_checker(cmd_list->cmds[i].cmds))
		cmd_list->cmds[i].cmds = wildcardings(cmd_list->cmds[i].cmds);
	define_input(&(cmd_list->cmds[i]), &(cmd_info.fd_in_out[0]),
		&info.pos_heredoc, &(cmd_info.in_out[0]));
	if (cmd_info.fd_in_out[0] == -1 && cmd_info.in_out[0] != HEREDOC)
		return (0) ;
	define_output(&(cmd_list->cmds[i]), &(cmd_info.fd_in_out[1]), &(cmd_info.in_out[1]));
	final_cmds = clean_cmds(&(cmd_list->cmds[i]), local);
	set_id_flag_cmd(final_cmds, &(cmd_list->cmds[i].id));
	cmd_info.id = cmd_list->cmds[i].id;
	if (cmd_info.id == UNDEFINED)
	{
		pid = fork();
		if (pid == 0)
		{
			switch_sig_default();
			res = solver(final_cmds, info, &cmd_info);
			exit(res);
		}
		waitpid(pid, &res, 0);
	}
	else	
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
		return (command_echo(cmds, local));
	else if (id == PWD)
		return (command_pwd());
	else if (id == EXPORT)
		return (command_export(cmds, local)) ;
	else if (id == ENV)
		return (command_env(local));
	else if (id == UNSET)
		return (command_unset(cmds, local));
	else if (id == PRINTENV)
		return (command_printenv(cmds, local));
	// // else if (id == EXIT)
	// // {
	// // 	command_exit(local_env, t_token *cmd_list, char ***heredocs);    como fazer?
	// // 	return ;
	// // }
	else if (id == CD)
		return (command_cd(cmds, local, 0));
	else if (id == UNDEFINED)
		return(command_execve(cmds, local, info, cmd_info));
	free(local);
	return (1);
}
