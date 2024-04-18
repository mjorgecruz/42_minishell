/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:55:30 by masoares          #+#    #+#             */
/*   Updated: 2024/04/18 15:38:19 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

int	command_pwd(t_localenv *local_env)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
	{
		ft_putendl_fd(cwd, 1);
		return (ex_code(EXIT_SUCCESS));
	}
	ft_putendl_fd(ft_getenv("PWD", local_env->content), 1);
	return (ex_code(EXIT_SUCCESS));
}

int	command_env(t_localenv *local)
{
	if (local == NULL)
		return (bi_err("local environment is NULL", "\n", ""));
	prtstr_arr_env(local->content);
	return (ex_code(EXIT_SUCCESS));
}

int	unset_variable(const char *variable, t_localenv *local)
{
	int	index;

	index = find_variable_index_recursive(variable, local->sorted, 0);
	if (index != -1)
	{
		free(local->sorted[index]);
		if (index >= 0)
		{
			while (local->sorted[index] != NULL)
			{
				local->sorted[index] = local->sorted[index + 1];
				index++;
			}
		}
		local->sorted[index] = NULL;
	}
	return (EXIT_SUCCESS);
}

int	unset_variable2(const char *variable, t_localenv *local)
{
	int	index;

	index = find_variable_index_recursive(variable, local->content, 0);
	if (index != -1)
	{
		free(local->content[index]);
		if (index >= 0)
		{
			while (local->content[index] != NULL)
			{
				local->content[index] = local->content[index + 1];
				index++;
			}
		}
		local->content[index] = NULL;
	}
	return (0);
}

int	command_unset(char **cmds, t_localenv *local)
{
	int	i;

	if (cmds == NULL || local == NULL || local->content == NULL)
		return (bi_err("Invalid command or local environment.", "\n", ""));
	if (cmds[1] == NULL)
		return (EXIT_SUCCESS);
	if (!isvar_valid(cmds[1]))
		return (0);
	i = 1;
	while (cmds[i] != NULL)
	{
		if (unset_variable(cmds[i], local) != 0)
			return (ex_code(EXIT_FAILURE));
		if (unset_variable2(cmds[i], local) != 0)
			return (ex_code(EXIT_FAILURE));
		i++;
	}
	return (ex_code(EXIT_SUCCESS));
}
