/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:55:30 by masoares          #+#    #+#             */
/*   Updated: 2024/04/16 13:58:24 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (index != 0)
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
		if (index != 0)
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
	int i;

	if (cmds == NULL || local == NULL || local->content == NULL)
		return (bi_err("Invalid command or local environment.", "\n", ""));
	if (cmds[1] == NULL)
		return (EXIT_SUCCESS);
	if (!isvar_valid(cmds[1]))
		return (EXIT_FAILURE + 1);
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

int	bi_err(char *str1, char *str2, char *str3)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str1, STDERR_FILENO);
	ft_putstr_fd(str2, STDERR_FILENO);
	ft_putstr_fd(str3, STDERR_FILENO);
	return (ex_code(EXIT_FAILURE));
}

int ex_code(int code)
{
	if (code == 298)
	{
		g_signal = 42;
		return(g_signal);
	}
	if (code >= 256 || code <= -256)
	{
		g_signal = WEXITSTATUS(code);
		return (g_signal);
	}
	if (code == 13)
		g_signal = 126;
	else
		g_signal = code;
	return (g_signal);
}
