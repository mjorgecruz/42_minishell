/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:08:35 by masoares          #+#    #+#             */
/*   Updated: 2024/04/19 13:51:51 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	file_name_replacer(char **file, char c);

int	solver(char **final_cmds, t_info info, t_cmd_info *cmd_info)
{
	int	res;

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
	int	fd;
	int	res;

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

	file = ft_strdup("");
	*i = ignore_spaces(cmd, *i);
	j = *i;
	while (cmd[j] && !ft_strchr("<>|& \t\n", cmd[j]))
	{
		if (ft_strchr("\"\'", cmd[*i]))
		{
			j++;
			while (cmd[j] && cmd[j] != cmd[*i])
			{
				file_name_replacer(&file, cmd[j]);
				j++;
			}
			j++;
		}
		else
			file_name_replacer(&file, cmd[j++]);
	}
	*i = j;
	return (file);
}

static void	file_name_replacer(char **file, char c)
{
	char	*garbage;
	char	*trav;

	trav = ft_calloc(2, sizeof(char));
	garbage = *file;
	trav[0] = c;
	*file = ft_strjoin(*file, trav);
	free(garbage);
	free(trav);
}
