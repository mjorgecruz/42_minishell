/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_setup_general.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:43:50 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/04/21 22:46:54 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	commands_sorter(t_token *cmd_list, t_info info, t_localenv *local)
{
	int	i;
	int	res;

	res = 0;
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
	while (cmd_list->next != NULL \
		&& (((res == 0 && cmd_list->next_type == D_PIPE)) 
		|| ((res != 0 && cmd_list->next_type == D_AMP))))
		cmd_list = cmd_list->next;
	if (cmd_list->next != NULL)
		commands_sorter(cmd_list->next, info, local);
	return ;
}

int	error_definer_(int *err, int *pos, char *cmds)
{
	char	*file;

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
