/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:55:30 by masoares          #+#    #+#             */
/*   Updated: 2024/01/29 11:55:48 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_echo(char **cmds)
{
    int i;
	bool n_flag;
	
	i = 0;
	n_flag = false;
	if (!ft_strcmp(cmds[1], "-n"))
	{
		n_flag = true;
		++i;
	}

    while (cmds[++i] != NULL)
        printf("%s ", cmds[i]);
    if (!n_flag)
		printf("\n");
	return (i);
}

int	command_pwd(void)
{
	static char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
	{
		ft_putendl_fd(cwd, 1);
		return (EXIT_SUCCESS);
	}
	else
		return (EXIT_FAILURE);
}
