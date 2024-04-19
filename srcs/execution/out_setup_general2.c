/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_setup_general2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:46:52 by masoares          #+#    #+#             */
/*   Updated: 2024/04/19 15:13:23 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

static int		code_verifier(int res);
static void	mega_piper(t_token *cmd_list, t_info info,
		t_localenv *local, int *pid);

int		mult_cmd_executer(t_token *cmd_list, t_info info,
		t_localenv *local, int i)
{
	int			*pid;
	int			res;

	while (cmd_list->cmds[i].cmds)
	 	i++;
	pid = (int *)malloc(sizeof(int) * i);
	i = 0;	
	mega_piper(cmd_list, info, local, pid);
	handle_sigint_status();
	i = 0;
	while (cmd_list->cmds[i].cmds)
	{
		waitpid(pid[i], &res, 0);
		i++;
	}
	code_verifier(res);
	return(free(pid), res);
}

static void		mega_piper(t_token *cmd_list, t_info info,
		t_localenv *local, int *pid)
{
	int		fd[2];
	int		res;
	int		i;
	int		stdin;
	
	res = 0;
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
	close(stdin);
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


static int		code_verifier(int res)
{
	ex_code(res);
	if (res == 2)
		printf("\n");
	else if (res == 131)
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	return (res);
}