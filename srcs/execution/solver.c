/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:08:35 by masoares          #+#    #+#             */
/*   Updated: 2024/04/18 16:53:10 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

int solver(char **final_cmds, t_info info, t_cmd_info *cmd_info)
{
	int		res;

	res = 0;
	if (cmd_info->fd_in_out[0] != STDIN_FILENO)
	{
		dup2(cmd_info->fd_in_out[0], STDIN_FILENO);
		close(cmd_info->fd_in_out[0]);
	}
	if (cmd_info->fd_in_out[1] == STDOUT_FILENO)
		res = exec_correct_builtin(final_cmds, info, cmd_info->id, *cmd_info);
	else if (cmd_info->fd_in_out[1] > STDOUT_FILENO)
		res = cd_output_exec(final_cmds, info, cmd_info->id, *cmd_info);
	return (res);
}

int	cd_output_exec(char **cmds, t_info info, t_builtin id, t_cmd_info cmd_info)
{
	int		fd;
	int		res;
	
	res = 0;
	fd = dup(STDOUT_FILENO);
	dup2(cmd_info.fd_in_out[1], STDOUT_FILENO);
	close(cmd_info.fd_in_out[1]);
	res = exec_correct_builtin(cmds, info, id, cmd_info);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (res);
}

char	*create_file_name(char *cmd, int *i)
{
	int		j;
	char	*file;
	char	*trav;
	char	*garbage;
	
	file = ft_strdup("");
	trav = ft_calloc(2, sizeof(char));
	*i = ignore_spaces(cmd, *i);
	j = *i;
	while (cmd[j] && !ft_strchr("<>|& \t\n", cmd[j]))
	{
		if (ft_strchr("\"\'", cmd[*i]))
		{
			j++;
			while (cmd[j] && cmd[j] != cmd[*i])
			{
				garbage = file;
				trav[0] = cmd[j];
				file = ft_strjoin(file, trav);
				free(garbage);
				j++;
			}
			j++;
		}
		else
		{
			garbage = file;
			trav[0] = cmd[j];
			file = ft_strjoin(file, trav);
			free(garbage);
			j++;
		}
	}
	*i = j;
	return (free(trav), file);
}
