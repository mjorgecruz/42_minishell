/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:55:30 by masoares          #+#    #+#             */
/*   Updated: 2024/04/04 15:39:16 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	print_string_array(char **strings)
{
	int	i;

	if (strings == NULL)
		return ;
	i = -1;
	while (strings[++i] != NULL)
		ft_printf("%s\n", strings[i]);
}

void	prtstr_arr_env(char **strings)
{
	int	i;

	if (strings == NULL)
		return ;
	i = -1;
	while (strings[++i] != NULL)
	{
		if (ft_strchr(strings[i], '='))
			ft_printf("%s\n", strings[i]);
	}
}

int	command_env(t_localenv *local)
{
	if (local == NULL)
		return (builtin_errors("local environment is NULL", "\n", ""));
	prtstr_arr_env(local->content);
	return (EXIT_SUCCESS);
}

int	unset_variable(const char *variable, t_localenv *local)
{
	int	index;

	index = find_variable_index(variable, local->content);
	if (index != -1)
	{
		free(local->content[index]);
		free(local->sorted[index]);
		while (local->content[index] != NULL)
		{
			local->content[index] = local->content[index + 1];
			local->sorted[index] = local->sorted[index + 1];
			index++;
		}
		local->content[index] = NULL;
		local->sorted[index] = NULL;
		return (EXIT_SUCCESS);
	}
	else
		return (EXIT_FAILURE);
}

int	command_unset(char **cmds, t_localenv *local)
{
	if (cmds == NULL || local == NULL || local->content == NULL)
		return (builtin_errors("Invalid command or local environment.", "\n", ""));
	if (cmds[1] == NULL)
		return (EXIT_SUCCESS);
	if (unset_variable(cmds[1], local) == 0)
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}

int builtin_errors(char *str1, char *str2, char *str3)
{
		ft_putstr_fd(str1, STDERR_FILENO);
		ft_putstr_fd(str2, STDERR_FILENO);
		ft_putstr_fd(str3, STDERR_FILENO);
	return(1);
}
