/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_setup_general.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:19:15 by masoares          #+#    #+#             */
/*   Updated: 2024/04/18 16:43:54 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

static int		error_definer_(int *err, int *pos, char *cmds);

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

int		inter_executioner(t_token *cmd_list, t_info info, t_localenv *local, int i)
{
	char		**final_cmds;
	t_cmd_info	cmd_info;
	int			j;
	int			res;
	int			err[2];
	int			pos[2];
	
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
		error_definer_(err, pos, cmd_list->cmds[i].cmds);
	final_cmds = clean_cmds(&(cmd_list->cmds[i]), local);
	set_lastcommand(final_cmds, info.local);
	res = all_data_to_solver(final_cmds, info, &cmd_info, cmd_list->cmds[i]);
	return (res);
}

static int		error_definer_(int *err, int *pos, char *cmds)
{
	char *file;
	
	if (pos[0] <= pos[1])
	{
		file = create_file_name(cmds, &pos[0]);
		if (err[0] == ENOENT)
			bi_err(file, " : No such file or directory", "\n");
		else if (err[0] == EACCES)
			bi_err(file, " : Permission denied", "\n");
		return (free(file), ex_code(1), g_signal);
	}
	else
	{
		file = create_file_name(cmds, &pos[1]);
		if (err[1] == ENOENT)
			bi_err(file, " : No such file or directory", "\n");
		else if (err[1] == EACCES)
			bi_err(file, " : Permission denied", "\n");
		else if (err[1] == 20)
			bi_err(file, " : Not a directory", "\n");
		return (free(file), ex_code(1), g_signal);
	}
}
