/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:58:03 by masoares          #+#    #+#             */
/*   Updated: 2024/04/19 13:20:02 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

void set_mesage(char *cmd, int code, char *msg)
{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd( msg, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		ex_code(code);
}

void err_eacces_chooser(char *cmd)
{
	DIR		*dir;
	dir = opendir(cmd);
	if (dir == NULL)
		set_mesage(cmd, 127, ": Permission denied");
	else
	{
		closedir(dir);
		set_mesage(cmd, 126, ": Is a directory");
	}
}

void err_enoent_chooser(char *cmd)
{
	if (ft_strchr(cmd, '/'))
		set_mesage(cmd, 127, " No such file or directory");
	else
		set_mesage(cmd, 127, ": command not found");
}

void exec_not(char *cmd)
{
	int i;
	int	count;

	count = 0;
	i = 0;
	while (cmd[i])
	{
		i = ignore_in_quotes(cmd, i);
		if (cmd[i] == '/')
			count++;
		if (cmd[i])
			i++;
	}
	if (errno == EACCES)
		err_eacces_chooser(cmd);
	else if (errno == ENOENT)
		err_enoent_chooser(cmd);

}
