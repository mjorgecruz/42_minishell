/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_setup_general.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:19:15 by masoares          #+#    #+#             */
/*   Updated: 2024/04/18 14:44:41 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

static	int	all_data_to_solver(char **final_cmds, t_info info, t_cmd_info	*cmd_info, t_command cmds);
static void cmd_info_starter(t_cmd_info	*cmd_info);
static void set_lastcommand(char **final_cmds, t_localenv *local);

void	commands_sorter(t_token *cmd_list, t_info info, t_localenv *local)
{
	int			i;
	int			res;

	res = -1;
	i = 0;
	info.token = cmd_list;
	if (cmd_list->down != NULL)
		commands_sorter(cmd_list->down, info, local);
	if (cmd_list && cmd_list->cmds)
	{
		if (cmd_list->cmds[i].cmds != 0 && cmd_list->cmds[i].cmds[0] != 0
			&& cmd_list->cmds[i + 1].cmds == NULL)
			res = inter_executioner(cmd_list, info, local, i);
		else
			res = mult_cmd_executer(cmd_list, info, local, i);
	}
	while (cmd_list->next != NULL 
		&& ((res == 0 && cmd_list->next_type == D_PIPE))) 
		cmd_list = cmd_list->next;
	if (cmd_list->next != NULL)	
		commands_sorter(cmd_list->next, info, local);
	return ;
}

int		mult_cmd_executer(t_token *cmd_list, t_info info,
		t_localenv *local, int i)
{
	int			*pid;
	int			stdin;
	int			fd[2];
	int			res;
	
	while (cmd_list->cmds[i].cmds)
	 	i++;
	pid = (int *)malloc(sizeof(int) * i);
	i = 0;	
	stdin = dup(STDIN_FILENO);
	while (cmd_list->cmds[i].cmds)
	{
		if (cmd_list->cmds[i].cmds[0] != 0)
		{
			pipe(fd);
			pid[i] = fork();
			if (pid[i] == 0)
			{
				switch_sig_default();
				pied_piper(cmd_list, fd, i, &stdin);
				free(pid);
				res = inter_executioner(cmd_list, info, local, i);
				tree_cleaner(info.head);
				free_info_andenv(info);
				exit(res);
			}
			dup2(fd[0], stdin);
			close(fd[0]);
			close(fd[1]);
		}
		i++;
	}
	handle_sigint_status();
	i = 0;
	while (cmd_list->cmds[i].cmds)
	{
		waitpid(pid[i], &res, 0);
		i++;
	}
	ex_code(res);
	if (res == 2)
		printf("\n");
	else if (res == 131)
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	close(stdin);
	return(free(pid), res);
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

int		waiter_function(t_token *cmd_list, int res)
{
	int		i;
	
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
	int			j;
	int			res;
	int			err[2];
	int			pos[2];
	char		*file;
	
	res = 0;
	j = 0;
	err[0] = 0;
	err[1] = 0;
	cmd_info_starter(&cmd_info);
	while (j < i)
	{
		define_input(&(cmd_list->cmds[j]), &(cmd_info.fd_in_out[0]),
			&info.pos_heredoc, &(cmd_info.in_out[0]));
		j++;
	}
	if (wildcard_checker(cmd_list->cmds[i].cmds))
		cmd_list->cmds[i].cmds = wildcardings(cmd_list->cmds[i].cmds);
	pos[0] = define_input(&(cmd_list->cmds[i]), &(cmd_info.fd_in_out[0]),	
		&info.pos_heredoc, &(cmd_info.in_out[0]));
	if (cmd_info.fd_in_out[0] == -1 && cmd_info.in_out[0] != HEREDOC)
		err[0] = errno;
	pos[1] = define_output(&(cmd_list->cmds[i]), &(cmd_info.fd_in_out[1]), &(cmd_info.in_out[1]), pos[0]);
	if (cmd_info.fd_in_out[1] == -1)
		err[1] = errno;
	if (err[1] != 0 || err[0] != 0)
	{
		if (pos[0] <= pos[1])
		{
			file = create_file_name(cmd_list->cmds[i].cmds, &pos[0]);
			if (err[0] == ENOENT)
				bi_err(file, " : No such file or directory", "\n");
			else if (err[0] == EACCES)
				bi_err(file, " : Permission denied", "\n");
			return (free(file), ex_code(1), g_signal);
		}
		else
		{
			file = create_file_name(cmd_list->cmds[i].cmds, &pos[1]);
			if (err[1] == ENOENT)
				bi_err(file, " : No such file or directory", "\n");
			else if (err[1] == EACCES)
				bi_err(file, " : Permission denied", "\n");
			else if (err[1] == 20)
				bi_err(file, " : Not a directory", "\n");
			return (free(file), ex_code(1), g_signal);
		}
	}
	final_cmds = clean_cmds(&(cmd_list->cmds[i]), local);
	set_lastcommand(final_cmds, info.local);
	res = all_data_to_solver(final_cmds, info, &cmd_info, cmd_list->cmds[i]);
	return (res);
}

static void set_lastcommand(char **final_cmds, t_localenv *local)
{
	int		i;

	i = 0;
	while (final_cmds[i])
		i++;
	i--;
	ft_setenv("_", final_cmds[i], local);
}

static void cmd_info_starter(t_cmd_info	*cmd_info)
{
	cmd_info->fd_in_out[0] = 0;
	cmd_info->fd_in_out[1] = 1;
	cmd_info->in_out[0] = UNDEF;
	cmd_info->in_out[1] = UNDEF;
}

static	int	all_data_to_solver(char **final_cmds, t_info info, t_cmd_info	*cmd_info, t_command cmds)
{
	int		res;
	int		pid;
	
	res = 0;
	set_id_flag_cmd(final_cmds, &(cmds.id));
	if (!final_cmds[0] || final_cmds[0][0] == 0)
		return(free_split(final_cmds), res);
	(*cmd_info).id = cmds.id;
	if ((*cmd_info).id == UNDEFINED || (*cmd_info).id == ECHOS)
	{
		pid = fork();
		if (pid == 0)
		{
			switch_sig_default();
			res = solver(final_cmds, info, cmd_info);
			free_info_andenv(info);
			tree_cleaner(info.head);
			free_split(final_cmds);
			exit(res);
		}
		handle_sigint_status();
		waitpid(pid, &res, 0);
		if (res == 2)
			printf("\n");
		else if (res == 131)
			bi_err("Quit (core dumped)", "\n", "");
		ex_code(res);
	}
	else	
	{
		res = solver(final_cmds, info, cmd_info);
		ex_code(res);
	}
	return(free_split(final_cmds), g_signal);
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
		return (command_echo(cmds));
	else if (id == PWD)
		return (command_pwd(local));
	else if (id == EXPORT)
		return (command_export(cmds, local));
	else if (id == ENV)
		return (command_env(local));
	else if (id == UNSET)
		return (command_unset(cmds, local));
	else if (id == PRINTENV)
		return (command_printenv(cmds, local));
	else if (id == EXIT)
		command_exit(info, cmds);
	else if (id == CD)
		return (command_cd(cmds, local, 0));
	else if (id == UNDEFINED)
		return(command_execve(cmds, local, info, cmd_info));
	return (g_signal);
}
