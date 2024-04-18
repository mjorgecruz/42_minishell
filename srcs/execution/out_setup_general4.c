/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_setup_general4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:51:49 by masoares          #+#    #+#             */
/*   Updated: 2024/04/18 16:23:21 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

void set_lastcommand(char **final_cmds, t_localenv *local)
{
	int		i;

	i = 0;
	while (final_cmds[i])
		i++;
	if (i > 0)
		i--;
	if (final_cmds[i] && final_cmds[i][0])
		ft_setenv("_", final_cmds[i], local);
}

void cmd_info_starter(t_cmd_info	*cmd_info)
{
	cmd_info->fd_in_out[0] = 0;
	cmd_info->fd_in_out[1] = 1;
	cmd_info->in_out[0] = UNDEF;
	cmd_info->in_out[1] = UNDEF;
}

int	all_data_to_solver(char **final_cmds, t_info info, t_cmd_info	*cmd_info, t_command cmds)
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
