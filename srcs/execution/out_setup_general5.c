/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_setup_general5.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:59:18 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/20 23:34:34 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_wild_n_her(t_token *cmd_list, int i, t_info info, t_cmd_info	cmd_info);

int	inter_executioner(t_token *cmd_list, t_info info, t_localenv *local, int i)
{
	char		**final_cmds;
	t_cmd_info	cmd_info;
	int			err[2];
	int			pos[2];

	err[0] = 0;
	err[1] = 0;
	cmd_info_starter(&cmd_info);
	count_wild_n_her(cmd_list, i, info, cmd_info);
	pos[0] = define_input(&(cmd_list->cmds[i]), &(cmd_info.fd_in_out[0]),	
		&info.pos_heredoc, &(cmd_info.in_out[0]));
	if (cmd_info.fd_in_out[0] == -1 && cmd_info.in_out[0] != HEREDOC)
		err[0] = errno;
	pos[1] = define_output(&(cmd_list->cmds[i]), &(cmd_info.fd_in_out[1]), &(cmd_info.in_out[1]), pos[0]);
	if (cmd_info.fd_in_out[1] == -1)
		err[1] = errno;
	if (err[1] != 0 || err[0] != 0)
		return (error_definer_(err, pos, cmd_list->cmds[i].cmds));
	final_cmds = clean_cmds(&(cmd_list->cmds[i]), local);
	set_lastcommand(final_cmds, info.local);
	return (all_data_to_solver(final_cmds, info, &cmd_info, cmd_list->cmds[i]));
}

int		count_wild_n_her(t_token *cmd_list, int i, t_info info, t_cmd_info	cmd_info)
{
	int		j;

	j = -1;
	while (++j < i)
		define_input(&(cmd_list->cmds[j]), &(cmd_info.fd_in_out[0]), \
		&info.pos_heredoc, &(cmd_info.in_out[0]));
	if (wildcard_checker(cmd_list->cmds[i].cmds))
		cmd_list->cmds[i].cmds = wildcardings(cmd_list->cmds[i].cmds);
	return (0);
}